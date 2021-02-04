//
// Created by QuantumRange on 04-Feb-21.
//

#ifndef RAYTRACER_FILE_IO_H
#define RAYTRACER_FILE_IO_H

#include <vector>
#include "Triangle.h"

void writeFile(std::string &filename, std::vector<Triangle> &triangles);

std::vector<Triangle> readFile(std::string filename);

#endif //RAYTRACER_FILE_IO_H
