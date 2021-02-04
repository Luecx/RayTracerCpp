//
// Created by QuantumRange on 04-Feb-21.
//

#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <string>
#include <ostream>

struct Pixel {
    Pixel(int r, int g, int b, int a);

    Pixel(int r, int g, int b);

    Pixel();

    int r;
    int g;
    int b;
    int a;
};

class Image {
private:
    int width;
    int height;
    Pixel **pixels;

public:
    Image(const int &width, const int &height);

    Image(Image &other);

    ~Image();

    void setPixel(int &x, int &y, Pixel &p);

    Pixel getPixel(int &x, int &y);

    void write(std::string filename);

    int getWidth() const;

    int getHeight() const;

    Pixel **getPixels() const;

    friend std::ostream &operator<<(std::ostream &os, const Image &image);

    bool operator<(const Image &rhs) const;

    bool operator>(const Image &rhs) const;

    bool operator<=(const Image &rhs) const;

    bool operator>=(const Image &rhs) const;

    bool operator==(const Image &rhs) const;

    bool operator!=(const Image &rhs) const;
};

Image loadImage(std::string &filename);

#endif //RAYTRACER_IMAGE_H
