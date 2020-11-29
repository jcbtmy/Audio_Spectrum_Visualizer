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

        int isopen();
        void swap();
        void poll();

};


#endif