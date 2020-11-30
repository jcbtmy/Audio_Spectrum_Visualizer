#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Controller{
    public:
        GLFWwindow *window;
        Controller(GLFWwindow* context){ window = context;}

        void handleEvents();
};


#endif 