#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <vector>
#include <map>

class Controller{
    public:

        float inputTransform[3] = {0.0f, 0.0f, 0.0f};
        bool spinObject = false;
        std::map<int, bool> keyMap;

        GLFWwindow *window;
        Controller(GLFWwindow* context){ window = context;}
        float* getRotation() {return &inputTransform[0];};
        void handleEvents();
        void updateTransform();
};


#endif 