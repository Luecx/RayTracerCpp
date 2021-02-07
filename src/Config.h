//
// Created by Luecx on 04.02.2021.
//

#ifndef RAYTRACER_CONFIG_H
#define RAYTRACER_CONFIG_H

#include <cstring>
#include <immintrin.h>
#include <ostream>

// put all adjustable double settings below
enum FPSettings{
    WIDTH,
    HEIGHT,
    FOV,                        // horizontal fov
    PIXEL_ASPECT,               // pixel fov (width / height)
    ANTIALIASING,               // how many samples in each direction for each pixel to average
    MAX_THREADS,                // how many threads to use for rendering
    KD_TREE_MAX_DEPTH,
    KD_TREE_MIN_ELEMENTS,
    SHADOW_SAMPLES_PER_PIXEL,
    END_DOUBLE_SETTINGS, // always have this at the end
};

class Config {

    double fpSettings[END_DOUBLE_SETTINGS];

public:
    Config();
    Config(const Config& config);
    Config(Config&& config);
    Config& operator=(const Config& config);
    Config& operator=(Config&& config);
    virtual ~Config();

    double& operator[](FPSettings fpSetting);
    double  operator[](FPSettings fpSetting) const;
};


#endif //RAYTRACER_CONFIG_H
