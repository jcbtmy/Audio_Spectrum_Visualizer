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

Window::~Window()
{
    glfwDestroyWindow(window);
}

int Window::isopen(){

    return !glfwWindowShouldClose(window);

}

void Window::swap(){
    glfwSwapBuffers(window);
}
