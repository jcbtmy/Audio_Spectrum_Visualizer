#include "Shape.h"


Shape::Shape(int stack_num)
{
    this->sphere(stack_num, 36, 1.0f);
    model = glm::mat4(1.0f);
}

Shape::~Shape()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void Shape::sphere(int stacks, int sectors, float radius)
{
    this->stacks = stacks;
    this->sectors = sectors;
    //implemented from http://www.songho.ca/opengl/gl_sphere.html
    const float PI = 3.14;
    float x,y,z, xy;
    float sectorStep = 2 * PI / sectors;
    float stackStep = PI / stacks;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stacks; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectors; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            copy.push_back(x);
            copy.push_back(y);
            copy.push_back(z);
        }
    }

    int k1, k2;
    for(int i = 0; i < stacks; ++i)
    {
        k1 = i * (sectors + 1);     // beginning of current stack
        k2 = k1 + sectors + 1;      // beginning of next stack

        for(int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }


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


   for(int i = 0; i < 6; i++){
        if(i < 2 || i > 3 ) 
            this->addIndex(i, i + 1, i + 2);
        if(i < 4){
            this->addIndex(i, i + 2, i + 4);
            (i % 2) ? this->addIndex(i, i + 3, i + 4) : this->addIndex(i, i + 1, i + 4);
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

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                this->getVerticesSize(),
                this->getVertices(),
                GL_DYNAMIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3*sizeof(float), (void*)0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                this->getIndicesSize(),
                this->getIndices(),
                GL_STATIC_DRAW);
    
}

void Shape::setUniform(unsigned int uni)
{
    uniform = uni;
}

void Shape::draw(){


    glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(model));
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, this->getVerticesSize(), this->getVertices(), GL_DYNAMIC_DRAW);

    glDrawElements(GL_TRIANGLES, 
                    (unsigned int) indices.size(), 
                    GL_UNSIGNED_INT, 
                    (void*)0);
}

void Shape::setRotation(float* input, int speed)
{
   if(!input)
        return;

    float movement_speed = 1.0f / (float) speed;
    glm::quat rotation =  glm::quat(glm::vec3(0,0,0));


    if(input[0] != 0.0f)
    {
         rotation *= glm::angleAxis((movement_speed * input[0]), glm::vec3(1.0, 0.0f, 0.0f));
    }
    if(input[1] != 0.0f)
    {
         rotation  *= glm::angleAxis((movement_speed * input[1]), glm::vec3(0.0, 1.0f, 0.0f));
    }
     if(input[2] != 0.0f)
    {
        rotation *= glm::angleAxis((movement_speed * input[2]), glm::vec3(0.0, 0.0f, 1.0f));
    }

    model = glm::toMat4(rotation) * model;
}

void Shape::useWireFrame(float lineWidth)
{
    glLineWidth( lineWidth);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void Shape::scaleStacks( float* scales)
{

    if(!scales)
        return;

    int update_location;
    float scale;

    for(int stack_number = 0; stack_number < stacks; stack_number++){

        update_location = stack_number * (sectors + 1) * 3;
        scale = 1.0f + (1.2f* sin((stack_number * M_PI)/(stacks + 2)) * (scales[stack_number]));
        for(int i = 0; i <= sectors * 3; i += 3)
        {
            vertices[update_location + i] = copy[update_location + i] * scale;
            vertices[update_location + i + 1] = copy[update_location + i + 1] * scale;
            vertices[update_location + i + 2] = copy[update_location + i + 2] * scale;

        }
    }


}
