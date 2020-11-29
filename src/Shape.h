#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

class Shape{

    public:

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        float*        getVertices() {return vertices.data();}
        unsigned int        getVerticesSize(){return (unsigned int)vertices.size() * sizeof(float);}

        unsigned int* getIndices(){return indices.data();}
        unsigned int        getIndicesSize() {return (unsigned int)indices.size()*sizeof(unsigned int);}
        Shape();

        void load();
        void draw();

};  


#endif