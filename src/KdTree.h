//
// Created by Luecx on 04.02.2021.
//

#ifndef RAYTRACER_KDTREE_H
#define RAYTRACER_KDTREE_H


#include <vector>
#include <algorithm>
#include "types.h"
struct KdNode{

    std::vector<Triangle> triangles{};
    KdNode* left  = nullptr;
    KdNode* right = nullptr;
    AABB    boundingBox{};


    KdNode(AABB aabb, std::vector<Triangle> p_triangles, int depth){
        this->boundingBox = aabb;
        if(depth == 0){
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

            for(Triangle& t:p_triangles){

            }

//            left  = new KdNode(triangles, depth-1);
//            right = new KdNode(triangles, depth-1);
        }
    }

    virtual ~KdNode() {
        if(left != nullptr){
            delete left;
            left = nullptr;
        }
        if(right != nullptr){
            delete right;
            right = nullptr;
        }
    }

};

class KdTree {

};


#endif //RAYTRACER_KDTREE_H
