//
// Created by QuantumRange on 04-Feb-21.
//

#include "Image.h"
#include <iostream>

Image::Image(const int &width, const int &height) {
    this->pixels = new Pixel *[width];

    for (int x = 0; x < width; x++) {
        this->pixels[x] = new Pixel[height];
    }

    this->width = width;
    this->height = height;
}

Image::Image(Image &other) {
    for (int x = 0; x < width; x++) {
        this->pixels[x] = new Pixel[height];

        for (int y = 0; y < height; y++) {
            this->pixels[x][y] = other.pixels[x][y];
        }
    }
}

Image::~Image() {
    for (int x = 0; x < width; x++) {
        delete[] pixels[x];
    }
    delete pixels;
}

void Image::setPixel(int &x, int &y, Pixel p) {
    this->pixels[x][y] = p;
}

Pixel Image::getPixel(int &x, int &y) {
    return this->pixels[x][y];
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

Pixel **Image::getPixels() const {
    return pixels;
}

std::ostream &operator<<(std::ostream &os, const Image &image) {
    os << "width: " << image.width << " height: " << image.height;
    return os;
}

bool Image::operator<(const Image &rhs) const {
    if (width < rhs.width)
        return true;
    if (rhs.width < width)
        return false;
    if (height < rhs.height)
        return true;
    if (rhs.height < height)
        return false;
    return true;
}

bool Image::operator>(const Image &rhs) const {
    return rhs < *this;
}

bool Image::operator<=(const Image &rhs) const {
    return !(rhs < *this);
}

bool Image::operator>=(const Image &rhs) const {
    return !(*this < rhs);
}

bool Image::operator==(const Image &rhs) const {
    return width == rhs.width &&
           height == rhs.height &&
           pixels == rhs.pixels;
}

bool Image::operator!=(const Image &rhs) const {
    return !(rhs == *this);
}

Pixel::Pixel(int r, int g, int b) : r(r), g(g), b(b) {}

Pixel::Pixel() : r(0), g(0), b(0) {}

Image loadImage(std::string &filename) {
    // TODO
    Image fa(5, 5);
    return fa;
}

void Image::write(std::string filename) {
    // https://en.wikipedia.org/wiki/BMP_file_format
    std::ofstream bmpFile(filename, std::ios::binary);

    BmpHeader header;
    BmpInfoHeader infoHeader;

    infoHeader.width = width;
    infoHeader.height = height;

    bmpFile.write((char *) &header, 14);
    bmpFile.write((char *) &infoHeader, 40);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            bmpFile.write((char *) &pixels[x][y], 3);
        }
    }

    bmpFile.close();
}
