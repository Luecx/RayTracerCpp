//
// Created by QuantumRange on 04-Feb-21.
//

#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <string>
#include <ostream>
#include <fstream>
#include <vector>

struct Pixel {
    Pixel(int r, int g, int b);

    Pixel();

    uint8_t b;
    uint8_t g;
    uint8_t r;
};

struct BmpHeader {
    char bitmapSignatureBytes[2] = {'B', 'M'};
    uint32_t sizeOfBitmapFile = 54 + 786432;
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;
};

struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width;
    int32_t height;
    uint16_t numberOfColorPlanes = 1;
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0;
    int32_t horizontalResolution = 3780;
    int32_t verticalResolution = 3780;
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;
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

    void setPixel(int &x, int &y, Pixel p);

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
