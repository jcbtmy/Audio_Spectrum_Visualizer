#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
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
        std::vector<unsigned int> indices;
        glm::mat4 model;

        unsigned int uniform;

        Shape();

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

};  


#endif