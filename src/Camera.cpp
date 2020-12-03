#include "Camera.h"


Camera::Camera(int width , int height)
{
    projection = glm::perspective(glm::radians(35.0f),(float) width / (float) height, 0.1f, 100.0f );
    
    view = glm::lookAt(
        glm::vec3(0,4,4),
        glm::vec3(0,0,0),
        glm::vec3(0, 1, 0)
    );

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
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
