//
// Created by Luecx on 04.02.2021.
//

#include "Config.h"

Config::Config() {
    (*this)[WIDTH]                    = 2560;
    (*this)[HEIGHT]                   = 1440;
    (*this)[FOV]                      = 80;
    (*this)[PIXEL_ASPECT]             = 1;
    (*this)[ANTIALIASING]             = 4;
    (*this)[MAX_THREADS]              = 24;
    (*this)[KD_TREE_MAX_DEPTH]        = 10;
    (*this)[KD_TREE_MIN_ELEMENTS]     = 2;
    (*this)[SHADOW_SAMPLES_PER_PIXEL] = 2;
}

Config::Config(const Config &config) {
    std::memcpy(fpSettings, config.fpSettings, END_DOUBLE_SETTINGS * sizeof(double));
}

Config::Config(Config &&config) {
    std::memcpy(fpSettings, config.fpSettings, END_DOUBLE_SETTINGS * sizeof(double));
}

Config &Config::operator=(const Config &config) {
    std::memcpy(fpSettings, config.fpSettings, END_DOUBLE_SETTINGS * sizeof(double));
    return *this;
}

Config &Config::operator=(Config &&config) {
    std::memcpy(fpSettings, config.fpSettings, END_DOUBLE_SETTINGS * sizeof(double));
    return *this;
}

Config::~Config() {}

double &Config::operator[](FPSettings fpSetting) {
    return fpSettings[fpSetting];
}

double Config::operator[](FPSettings fpSetting) const {
    return fpSettings[fpSetting];
}
