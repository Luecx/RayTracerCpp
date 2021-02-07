//
// Created by Luecx on 06.02.2021.
//

#ifndef RAYTRACER_RENDER_H
#define RAYTRACER_RENDER_H


#include "scene.h"
#include "omp.h"

struct RenderBuffer{

    double* data;
    int width;
    int height;

    RenderBuffer(int w, int h) : width(w), height(h){
        this->data = new double [w*h];
    }

    RenderBuffer(const RenderBuffer &renderBuffer){
        this->width = renderBuffer.width;
        this->height = renderBuffer.height;
        this->data = new double[width*height];
        std::memcpy(this->data, renderBuffer.data, sizeof(double) * this->width * this->height);
    }

    RenderBuffer(RenderBuffer &&renderBuffer){
        this->width = renderBuffer.width;
        this->height = renderBuffer.height;
        this->data = new double[width*height];
        std::memcpy(this->data, renderBuffer.data, sizeof(double) * this->width * this->height);
        renderBuffer.data = nullptr;
    }

    virtual ~RenderBuffer() {
        if(data != nullptr)
            delete[] data;
    }

    RenderBuffer& operator=(const RenderBuffer& other){
        if(this->width != other.width || this->height != other.height){
            delete[] data;
            this->width = other.width;
            this->height = other.height;
            this->data = new double[width*height];
        }
        std::memcpy(this->data, other.data, sizeof(double) * this->width * this->height);
        return *this;
    }

    RenderBuffer& operator=(RenderBuffer&& other) noexcept {
        if(this->width != other.width || this->height != other.height){
            delete[] data;
            this->width = other.width;
            this->height = other.height;
            this->data = new double[width*height];
        }
        this->data = other.data;
        other.data = nullptr;
        return *this;
    }

    double& at(int w, int h){
        return data[h * width + w];
    }

    double get(int w, int h) const{
        return data[h * width + w];
    }


};

struct Renderer{

public:


    Image render(Scene& scene, Config& config){
        this->config = config;
        this->scene  = scene;
        this->render_image          = new Image(config[WIDTH]*config[ANTIALIASING], config[HEIGHT]*config[ANTIALIASING]);
        this->antialiased_image     = new Image(config[WIDTH]                     , config[HEIGHT]                     );
        this->shadowBuffer          = new RenderBuffer*[scene.lights.size()];
        this->lightIntensityBuffer  = new RenderBuffer*[scene.lights.size()];

        for(int i = 0; i < scene.lights.size(); i++){
            shadowBuffer[i]         = new RenderBuffer(config[WIDTH]*config[ANTIALIASING], config[HEIGHT]*config[ANTIALIASING]);
            lightIntensityBuffer[i] = new RenderBuffer(config[WIDTH]*config[ANTIALIASING], config[HEIGHT]*config[ANTIALIASING]);
        }


        int     rows     = config[HEIGHT]*config[ANTIALIASING];
        auto    start    = clock();
        int     progress = 0;
#pragma omp parallel for schedule(static) num_threads((int)config[MAX_THREADS])
        for(int j = 0; j < rows; j++){
            for(int i = 0; i < config[WIDTH]*config[ANTIALIASING]; i++){
                double x = -1.0 + 2.0 * i / (config[WIDTH ] * config[ANTIALIASING] - 1);
                double y =  1.0 - 2.0 * j / (config[HEIGHT] * config[ANTIALIASING] - 1);
                render(computeRay(x,y), i,j);
            }
            std::cout   <<"\r"
                    << "progress: " <<  (++progress) * 100.0 / rows                << " %   "
                    << "time: "     <<  (clock() - start) / 1000.0          << " s   "
                    << std::flush;

        }

        antialias();
        Image out = *antialiased_image;
        finishRendering();
        return out;
    }

    virtual ~Renderer() {

    }

private:
    RenderBuffer** shadowBuffer;
    RenderBuffer** lightIntensityBuffer;

    Scene scene;
    Image* antialiased_image    = nullptr;
    Image* render_image         = nullptr;

    Config config;

    // x and y in range of -1 to 1 (screen space)
    Ray computeRay(double x, double y){
        double horizontal_fov  = config[FOV];
        double vertical_fov    = config[HEIGHT] / config[WIDTH] * config[FOV] / config[PIXEL_ASPECT];

        double max_half_width  = std::atan(2.0 / 360.0 * 3.1415926535 * horizontal_fov / 2);
        double max_half_height = std::atan(2.0 / 360.0 * 3.1415926535 * vertical_fov   / 2);

        Vector right     = scene.camera.direction.cross(scene.camera.up);
        
        Vector base      = scene.camera.position;
        Vector direction = scene.camera.direction
                + scene.camera.up * y * max_half_height
                +           right * x * max_half_width;
        direction       *= 1.0 / direction.mag();

        Ray r = {base, direction};
        return r;
    }

    void render(Ray r, int i, int j){

        HitData t{};
        double d     = intersect_ray_kdtree(r, *scene.models[0],t);

        Vector norm  = t.triangle.getNormal(t.coordinate);
        norm        *= (1 / norm.mag());

        if(d < INFTY){

                Pixel p{
                    (int)(127 * (1 + norm[0])),
                    (int)(127 * (1 + norm[1])),
                    (int)(127 * (1 + norm[2]))};
//            Pixel p {
//                    (int)(255 * t.coordinate.w),
//                    (int)(255 * t.coordinate.u),
//                    (int)(255 * t.coordinate.v),
//            };
            render_image->setPixel(i,j,p);
        }
    }

    void antialias(){
        for(int i = 0; i < config[WIDTH]; i++){
            for(int j = 0; j < config[HEIGHT]; j++){
                double r_sum = 0, g_sum = 0, b_sum = 0, a_sum = 0;
                for(int x = i * config[ANTIALIASING]; x < (i+1) * config[ANTIALIASING]; x++){
                    for(int y = j * config[ANTIALIASING]; y < (j+1) * config[ANTIALIASING]; y++){
                        r_sum += render_image->getPixel(x,y).r;
                        g_sum += render_image->getPixel(x,y).g;
                        b_sum += render_image->getPixel(x,y).b;
                        a_sum += render_image->getPixel(x,y).a;
                    }
                }

                r_sum /= config[ANTIALIASING] * config[ANTIALIASING];
                g_sum /= config[ANTIALIASING] * config[ANTIALIASING];
                b_sum /= config[ANTIALIASING] * config[ANTIALIASING];
                a_sum /= config[ANTIALIASING] * config[ANTIALIASING];

                antialiased_image->setPixel(i,j,{(int)r_sum, (int)g_sum, (int)b_sum, (int)a_sum});
            }
        }
    }

    void finishRendering(){
        if(antialiased_image != nullptr){
            delete antialiased_image;
            antialiased_image = nullptr;
        }
        if(render_image != nullptr){
            delete render_image;
            render_image = nullptr;
        }
        if(shadowBuffer != nullptr){
            for(int i = 0; i < scene.lights.size(); i++){
                delete shadowBuffer[i];
                delete lightIntensityBuffer[i];
            }
            delete[] shadowBuffer;
            delete[] lightIntensityBuffer;
            shadowBuffer            = nullptr;
            lightIntensityBuffer    = nullptr;
        }
    }
};



#endif //RAYTRACER_RENDER_H
