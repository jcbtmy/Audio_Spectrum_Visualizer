#include "Window.h"



Window::Window(int width, int height, const char* title)
{
    if(!glfwInit())
    {
        exit(1);
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if(!window)
    {
        std::cout << "Error Creating Window" << "\n";
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);
}

int Window::isopen(){

    return !glfwWindowShouldClose(window);

}

void Window::swap(){
    glfwSwapBuffers(window);
}

void Window::poll(){
    glfwPollEvents();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
}