//
// Created by QuantumRange on 04-Feb-21.
//

#include <fstream>
#include <iostream>
#include <regex>
#include "file_io.h"

std::vector<std::string> split(const std::string str, const std::string regex_str) {   // a yet more concise form!
    std::regex regexz(regex_str);
    std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
                                  std::sregex_token_iterator());
    return list;
}

void writeFile(const std::string &filename, std::vector<Triangle> &triangles) {
    std::ofstream myfile (filename);
    if (myfile.is_open()){

        for(Triangle& t:triangles){
            myfile << "v " << t.getA().position[0] << " " << t.getA().position[1] << " " << t.getA().position[2] << "\n";
            myfile << "v " << t.getB().position[0] << " " << t.getB().position[1] << " " << t.getB().position[2] << "\n";
            myfile << "v " << t.getC().position[0] << " " << t.getC().position[1] << " " << t.getC().position[2] << "\n";
        }

        int index = 1;
        for(Triangle& t:triangles){
            myfile << "f " << (index ++) << " " << (index ++) << " " << (index ++) << "\n";
        }

    }else{
        std::cout << "could not open " << filename << std::endl;
    }
    myfile.close();
}

std::vector<Triangle> readFile(const std::string &filename) {
    std::string text;

    std::ifstream File(filename);

    std::vector<Vector>         vertices;
    std::vector<Vector>         normals;
    std::vector<Triangle>       triangles;
    bool isV;

    while (getline(File, text)) {


        std::vector<std::string> args = split(text, " ");
        if(args.empty()) continue;
        if(args[0] == "v"){
            vertices.emplace_back(
                    std::stod(args[1]),
                    std::stod(args[2]),
                    std::stod(args[3]));
        }else if(args[0] == "vt"){

        }else if(args[0] == "vn"){
            normals.emplace_back(
                    std::stod(args[1]),
                    std::stod(args[2]),
                    std::stod(args[3]));
        }else if(args[0] == "f"){
            std::vector<std::string> nd1 = split(args[1], "/");
            std::vector<std::string> nd2 = split(args[2], "/");
            std::vector<std::string> nd3 = split(args[3], "/");

            TriangleNode node1{};
            TriangleNode node2{};
            TriangleNode node3{};

            if(nd1.size() >= 1){node1.position = vertices[std::stoi(nd1[0])-1];}
            if(nd2.size() >= 1){node2.position = vertices[std::stoi(nd2[0])-1];}
            if(nd3.size() >= 1){node3.position = vertices[std::stoi(nd3[0])-1];}

            if(nd1.size() >= 3){node1.normal = normals[std::stoi(nd1[2])-1];}
            if(nd2.size() >= 3){node2.normal = normals[std::stoi(nd2[2])-1];}
            if(nd3.size() >= 3){node3.normal = normals[std::stoi(nd3[2])-1];}

            if(node1.normal.mag() * node2.normal.mag() * node3.normal.mag() == 0){
                Vector normal = (node2.position - node1.position).cross(node3.position - node1.position);
                normal *= 1.0 / normal.mag();
                node1.normal = node2.normal = node3.normal = normal;
            }

            triangles.emplace_back(node1,node2,node3);
        }


//        isV = text[0] == 'v';
//
//        if ((isV || text[0] == 'f') && text[1] == ' ') {
//            text.erase(0, 2);
//
//            int tempI = text.find(' ');
//            std::string a = text.substr(0, tempI);
//
//            text.erase(0, tempI + 1);
//            tempI = text.find(' ');
//            std::string b = text.substr(0, tempI);
//
//            text.erase(0, tempI + 1);
//            tempI = text.find(' ');
//            std::string c = text.substr(0, tempI);
//
//            if (isV) {
//                vertices.emplace_back(atof(a.c_str()), atof(b.c_str()), atof(c.c_str()));
//            } else {
//                std::string fa = a.substr(0, a.find('/'));
//                std::string fb = b.substr(0, b.find('/'));
//                std::string fc = c.substr(0, c.find('/'));
//
//                TriangleNode node1{};
//                TriangleNode node2{};
//                TriangleNode node3{};
//
//                node1.position = vertices[std::stoi(fa) - 1];
//                node2.position = vertices[std::stoi(fb) - 1];
//                node3.position = vertices[std::stoi(fc) - 1];
//
//
//
//                Triangle t(node1,node2,node3);
//
//                triangles.push_back(t);
//            }
//        }

    }


    return triangles;
}
