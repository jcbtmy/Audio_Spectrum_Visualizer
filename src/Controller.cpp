#include "Controller.h"


void Controller::handleEvents()
{
    glfwPollEvents();
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
}