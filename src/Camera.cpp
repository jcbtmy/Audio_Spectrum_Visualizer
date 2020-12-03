#include "Camera.h"


Camera::Camera(int width , int height)
{
    projection = glm::perspective(glm::radians(45.0f),(float) width / (float) height, 0.1f, 100.0f );
    
    view = glm::lookAt(
        glm::vec3(4,3,3),
        glm::vec3(0,0,0),
        glm::vec3(0, 1, 0)
    );
}

void Camera::setRotation(float* input, int speed)
{
    if(!input)
        return;

    float movement_speed = 45.0f / (float) speed;

    if(input[0] != 0.0f)
    {
         view = glm::rotate(view,
                            (float)glm::radians(movement_speed * input[0]),
                                glm::vec3(1.0, 0.0f, 0.0f));
    }

    if(input[1] != 0.0f)
    {
        view = glm::rotate(view,
                                (float)glm::radians(movement_speed * input[1]),
                                glm::vec3(0.0, 1.0f, 0.0f));
    }

     if(input[2] != 0.0f)
    {
        view = glm::rotate(view,
                                (float)glm::radians(movement_speed * input[2]),
                                glm::vec3(0.0, 0.0f, 1.0f));
    }

}

void Camera::update()
{
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
}

void Camera::setUniforms(unsigned int uniformProjection, unsigned int uniformView)
{
    this->uniformProjection = uniformProjection;
    this->uniformView = uniformView;
}
