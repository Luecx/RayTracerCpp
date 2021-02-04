//
// Created by Luecx on 04.02.2021.
//

#ifndef RAYTRACER_KDTREE_H
#define RAYTRACER_KDTREE_H


#include <vector>
struct KdNode{

    std::vector<Triangle> triangles{};
//    KdNode* left  = nullptr;
//    KdNode* right = nullptr;

    KdNode(std::vector<Triangle> p_triangles, int depth){
        if(depth == 0){
            this->triangles.insert(this->triangles.end(), p_triangles.begin(), p_triangles.end());
        }else{
////            left  = new KdNode(triangles, depth-1);
////            right = new KdNode(triangles, depth-1);
        }
    }

    virtual ~KdNode() {
//        if(left != nullptr){
//            delete left;
//            left = nullptr;
//        }
//        if(right != nullptr){
//            delete right;
//            right = nullptr;
//        }
    }

};

class KdTree {

};


#endif //RAYTRACER_KDTREE_H
