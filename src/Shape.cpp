#include "Shape.h"


Shape::Shape()
{
    this->cube(0.5f);
}

void Shape::square(float step){

    float x, y;
    unsigned int i1, i2;

    for(int i = 0; i < 2; i++){
        x = i - step;
        i1 = i;
        for(int j = 0; j < 2; j++){
            i2 = i + 1;
            y = j - step;
            this->addVertex(x,y,0.f);
        }
        this->addIndex(i1, i2, i2 + 1);
    }

}

void Shape::cube(float step)
{
    const int sides = 6;
    float x,y,z;
    unsigned int index_count;
    unsigned int i1,i2,i3;

    //x coordinates
    for(int i = 0; i < 2; i++)
    {
        x = i - step;
        //y coordinates
        for(int j = 0; j < 2; j++)
        {
            y = j - step;
            //z coordinates
            for(int k = 0; k < 2; k++)
            {
                z = k - step;
                this->addVertex(x,y,z);
            }
        }
    }

    for(int i = 0; i < sides; i++)
    {
        
        this->addIndex(i, i + 1, i + 2);
        if(i < 4)
        {
           ( i % 2 == 0) ? i2 = 1 : i2 = 2;  
           this->addIndex(i, i + i2, i + 4);
           this->addIndex(i, i + i2 + 1, i + 4);
        }

    }


}

void Shape::addVertex(float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}

void Shape::addIndex(unsigned int i1, unsigned int i2, unsigned int i3)
{
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
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