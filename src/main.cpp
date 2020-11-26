#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

struct ScreenDim {
    int width;
    int height;
    int refresh_rate;
} typedef screenDim;

void get_resolution(int* width, int* height, int* refresh_rate) {
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    *width = mode->width;
    *height = mode->height;
    *refresh_rate = mode->refreshRate;

}

static void blue_screen(GLFWwindow* window) {
    glClearColor(0.25, 0.25, 0.25, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

}

static void full_screen(GLFWwindow* window, GLFWmonitor* monitor, ScreenDim* dims){

    static bool fullscreen = false;

    glfwPollEvents();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
        return;
    }
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
        if(!fullscreen) glfwSetWindowMonitor(window, monitor, 0,0, dims->width, dims->height, dims->refresh_rate);
        if(fullscreen) glfwSetWindowMonitor(window, NULL, 0 ,0 , dims->height, dims->width, dims->refresh_rate);
        fullscreen = !fullscreen;
        printf("width: %d || height: %d\n", dims->width ,dims->height);
    }
}


int main(void){

    GLFWwindow* window;
    GLFWmonitor* monitor;
    ScreenDim dims;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    monitor = glfwGetPrimaryMonitor();
    get_resolution(&(dims.width), &(dims.height), &(dims.refresh_rate));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        
        blue_screen(window);

        full_screen(window, monitor, &dims);
    

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}