#include "Controller.h"
#include <iostream>


void Controller::handleEvents()
{
    glfwPollEvents();
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
    this->updateTransform();
}

void Controller::updateTransform()
{
    bool up, down, left, right;
    spinObject = false;

    for(int i = 0; i < 3; i++){
        inputTransform[i] = 0.0f;
    } 
    
    if((up = glfwGetKey(window, GLFW_KEY_W)) == GLFW_PRESS)
    {
        //spin on x axis
        inputTransform[0] = 1.0f;
    }
    if((down = glfwGetKey(window, GLFW_KEY_S)) == GLFW_PRESS)
    {
        inputTransform[0] = -1.0f;
    }
    if((right = glfwGetKey(window, GLFW_KEY_D)) == GLFW_PRESS)
    {
        //spin on y axis
        inputTransform[1] = -1.0f;
    }
    if((left = glfwGetKey(window, GLFW_KEY_A)) == GLFW_PRESS)
    {
        inputTransform[1] = 1.0f;
    }

    if( up || down || right || left)
    {
        spinObject = true;
    }
}