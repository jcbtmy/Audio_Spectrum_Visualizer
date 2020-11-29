#include "Shape.h"


Shape::Shape()
{
    vertices.push_back(-0.5f);
    vertices.push_back(-0.5f);
    vertices.push_back(0.0f);

    vertices.push_back(0.5f);
    vertices.push_back(-0.5f);
    vertices.push_back( 0.0f);

    vertices.push_back(0.5f);
    vertices.push_back(0.5f);
    vertices.push_back(0.0f);

    vertices.push_back(-0.5f);
    vertices.push_back(0.5f);
    vertices.push_back(0.0f);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);

}

void Shape::load(){

    unsigned int vbo;
    unsigned int ibo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                this->getVerticesSize(),
                this->getVertices(),
                GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3*sizeof(float), (void*)0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                this->getIndicesSize(),
                this->getIndices(),
                GL_STATIC_DRAW);
}

void Shape::draw(){
    glDrawElements(GL_TRIANGLES, 
                    (unsigned int) indices.size(), 
                    GL_UNSIGNED_INT, 
                    (void*)0);
}