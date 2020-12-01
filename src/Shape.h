#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

class Shape{

    public:

        std::chrono::system_clock::time_point t_start ;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        unsigned int shaderProgram;
        unsigned int uniTrans;

        float*        getVertices() {return vertices.data();}
        unsigned int        getVerticesSize(){return (unsigned int)vertices.size() * sizeof(float);}

        unsigned int* getIndices(){return indices.data();}
        unsigned int        getIndicesSize() {return (unsigned int)indices.size()*sizeof(unsigned int);}
        Shape(unsigned int shader);

        void square(float step);
        void cube(float step);
        void addVertex(float, float, float);
        void addIndex(unsigned int, unsigned int, unsigned int);

        void load();
        void draw();
        void spin();

};  


#endif