//
// Created by Luecx on 04.02.2021.
//

#include "KdTree.h"


KdTree::KdTree(std::vector<Triangle> p_triangles, int depth, int minElements) {
    create(computeBoundingbox(p_triangles), p_triangles, depth, minElements);
}

KdTree::KdTree(AABB aabb, std::vector<Triangle> p_triangles, int depth, int minElements) {
    create(aabb, p_triangles, depth, minElements);
}

void KdTree::create(AABB aabb, std::vector<Triangle> p_triangles, int depth, int minElements) {
    this->boundingBox = aabb;
    if(depth == 0 || p_triangles.size() <= minElements){
        this->triangles.insert(this->triangles.end(), p_triangles.begin(), p_triangles.end());
    }else{

        // figure out to split along which axis
        int longestAxis = 0;
        double longestAxisLength = boundingBox.max[0] - boundingBox.min[0];
        for(int i = 1; i < 3; i++){
            double length = boundingBox.max[i] - boundingBox.min[i];
            if(length > longestAxisLength){
                longestAxisLength = length;
                longestAxis = i;
            }
        }
        std::sort (p_triangles.begin(), p_triangles.end(),
                   [longestAxis](Triangle &t1, Triangle &t2)
                   {return t1.center()[longestAxis]
                           < t2.center()[longestAxis];});

        std::size_t const half_size = p_triangles.size() / 2;
        std::vector<Triangle> split_lo(p_triangles.begin(), p_triangles.begin() + half_size);
        std::vector<Triangle> split_hi(p_triangles.begin() + half_size, p_triangles.end());

        double cutPosition = aabb.max[longestAxis] - aabb.min[longestAxis];
        if(p_triangles.size() > 1){
            // determine the cut position by taking the average of the closest triangles to the cut
            cutPosition = (split_lo[split_lo.size()-1].center() + split_hi[0].center())[longestAxis] * 0.5;
        }
        // determine the cut plane
        Plane cutPlane{{0,0,0},{0,0,0}};
        cutPlane.normal[longestAxis] = 1;
        cutPlane.base  [longestAxis] = cutPosition;

        int trianglesLeft  = split_lo.size();
        int trianglesRight = split_hi.size();
        for(int i = 0; i < trianglesLeft; i++){
            split_lo[i].splitTriangle(cutPlane, split_lo, split_hi, -1);
        }
        for(int i = 0; i < trianglesRight; i++){
            split_hi[i].splitTriangle(cutPlane, split_lo, split_hi, +1);
        }

        AABB aabbLeft  = {aabb.min, aabb.max};
        AABB aabbRight = {aabb.min, aabb.max};

        aabbLeft .max[longestAxis] = cutPosition;
        aabbRight.min[longestAxis] = cutPosition;

        left  = new KdTree(aabbLeft,  split_lo, depth-1, minElements);
        right = new KdTree(aabbRight, split_hi, depth-1, minElements);
    }
}

KdTree::~KdTree() {
    if(left != nullptr){
        delete left;
        left = nullptr;
    }
    if(right != nullptr){
        delete right;
        right = nullptr;
    }
}

AABB KdTree::computeBoundingbox(std::vector<Triangle> p_triangles) {
    Vector min{ 100000000, 100000000, 100000000};
    Vector max{-100000000,-100000000,-100000000};

    for(Triangle& t:p_triangles){
        for(int n = 0; n < 3; n++){
            min[0] = std::min(t[n].position[0], min[0]);
            min[1] = std::min(t[n].position[1], min[1]);
            min[2] = std::min(t[n].position[2], min[2]);
            max[0] = std::max(t[n].position[0], max[0]);
            max[1] = std::max(t[n].position[1], max[1]);
            max[2] = std::max(t[n].position[2], max[2]);
        }
    }
    return {min, max};
}
