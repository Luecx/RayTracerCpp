//
// Created by QuantumRange on 04-Feb-21.
//

#include <fstream>
#include <iostream>
#include "file_io.h"

void writeFile(const std::string &filename, std::vector<Triangle> &triangles) {
    std::ofstream myfile (filename);
    if (myfile.is_open()){

        for(Triangle& t:triangles){
            myfile << "v " << t.getA()[0] << " " << t.getA()[1] << " " << t.getA()[2] << "\n";
            myfile << "v " << t.getB()[0] << " " << t.getB()[1] << " " << t.getB()[2] << "\n";
            myfile << "v " << t.getC()[0] << " " << t.getC()[1] << " " << t.getC()[2] << "\n";
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

    std::vector<Vector> vertices;
    std::vector<Triangle> triangles;
    bool isV;

    while (getline(File, text)) {
        isV = text[0] == 'v';

        if ((isV || text[0] == 'f') && text[1] == ' ') {
            text.erase(0, 2);

            int tempI = text.find(' ');
            std::string a = text.substr(0, tempI);

            text.erase(0, tempI + 1);
            tempI = text.find(' ');
            std::string b = text.substr(0, tempI);

            text.erase(0, tempI + 1);
            tempI = text.find(' ');
            std::string c = text.substr(0, tempI);

            if (isV) {
                vertices.emplace_back(atof(a.c_str()), atof(b.c_str()), atof(c.c_str()));
            } else {
                std::string fa = a.substr(0, a.find('/'));
                std::string fb = b.substr(0, b.find('/'));
                std::string fc = c.substr(0, c.find('/'));

                Triangle t(vertices[std::stoi(fa) - 1], vertices[std::stoi(fb) - 1], vertices[std::stoi(fc) - 1]);

                triangles.push_back(t);
            }
        }

    }


    return triangles;
}
