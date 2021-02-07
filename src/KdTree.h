//
// Created by Luecx on 04.02.2021.
//

#ifndef RAYTRACER_KDTREE_H
#define RAYTRACER_KDTREE_H


#include <vector>
#include <algorithm>
#include "types.h"
#include "file_io.h"
#include <iostream>

struct KdTree{

    std::vector<Triangle> triangles{};
    KdTree* left  = nullptr;
    KdTree* right = nullptr;
    AABB    boundingBox{};

    KdTree(const KdTree& other) = delete;
    KdTree(KdTree&& other)      = delete;

    KdTree(std::vector<Triangle> p_triangles, int depth, int minElements);

    KdTree(AABB aabb, std::vector<Triangle> p_triangles, int depth, int minElements);

    void create(AABB aabb, std::vector<Triangle> p_triangles, int depth, int minElements);

    virtual ~KdTree();

    AABB computeBoundingbox(std::vector<Triangle> p_triangles);
};



#endif //RAYTRACER_KDTREE_H
