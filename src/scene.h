//
// Created by Luecx on 06.02.2021.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "vector"
#include "Config.h"

class Scene{
public:

    std::vector<Light  > lights{};
    std::vector<KdTree*> models{};
    KdTree* kdTree;
    Camera  camera;

    void addModel(std::vector<Triangle> &triangles, Config& config){
//        kdNodes.emplace_back(triangles, config[KD_TREE_MAX_DEPTH], config[KD_TREE_MIN_ELEMENTS]);
//        kdTree.create(triangles, config[KD])
        models.emplace_back(new KdTree(triangles, config[KD_TREE_MAX_DEPTH], config[KD_TREE_MIN_ELEMENTS]));
    }

    void addLight(Light &light){
        lights.emplace_back(light);
    }

    void setCamera(Camera &r){
        camera = r;
        camera.direction *= (1.0 / camera.direction.mag());
        camera.up        *= (1.0 / camera.up       .mag());
    }


};

#endif //RAYTRACER_SCENE_H
