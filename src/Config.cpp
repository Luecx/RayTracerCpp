//
// Created by Luecx on 04.02.2021.
//

#include "Config.h"

Config::Config() {
    (*this)[WIDTH]              = 720;
    (*this)[HEIGHT]             = 480;
    (*this)[KD_TREE_MAX_DEPTH]  = 8;
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
