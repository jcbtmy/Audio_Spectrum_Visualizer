#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <math.h>

class Shape{

    public:
        std::vector<float> vertices;
        std::vector<float> copy;
        std::vector<unsigned int> indices;
        glm::mat4 model;

        int stacks, sectors, last_stack = 0;
        unsigned int uniform;
        unsigned int vbo;

        Shape(int stack_num);

        float*        getVertices() {return vertices.data();}
        unsigned int  getVerticesSize(){return (unsigned int)vertices.size() * sizeof(float);}

        unsigned int* getIndices(){return indices.data();}
        unsigned int  getIndicesSize() {return (unsigned int)indices.size()*sizeof(unsigned int);}

        void square(float step);
        void cube(float step);
        void sphere(int stacks, int sectors, float radius);
        void addVertex(float, float, float);
        void addIndex(unsigned int, unsigned int, unsigned int);
        void setUniform(unsigned int);

        void load();
        void draw();
        void setRotation(float* input, int speed);
        void useWireFrame(float lineWidth);
        void scaleStacks(int time, float* scales);

};  


#endif