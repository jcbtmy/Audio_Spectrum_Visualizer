#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Window{

    public:

        GLFWwindow* window;
        bool last_key;

        Window(int width, int height, const char*);

        GLFWwindow* getContext() {return window;}
        int isopen();
        void swap();


};


#endif