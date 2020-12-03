
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "Window.h"
#include "Shader.h"
#include "Sphere.h"
#include "Shape.h"
#include "Controller.h"
#include "Camera.h"


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

static void gray_screen() {
    glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



int main(void){

    GLFWmonitor* monitor;
    ScreenDim dims;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    Window window(1080, 720, "Hello World");
    Controller controller(window.getContext());

    glewExperimental = GL_TRUE;
    glewInit();

    monitor = glfwGetPrimaryMonitor();
    get_resolution(&(dims.width), &(dims.height), &(dims.refresh_rate));

    Shader shader("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    Shape shape;
    Camera camera(dims.width, dims.height);


    //glLineWidth(1.0f);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // Accept fragment if it closer to the camera than the former one
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    camera.setUniforms(shader.getUniform("projection"), shader.getUniform("view"));
    shape.setUniform(shader.getUniform("model"));

    shape.load();
    shader.use();
    
    while (window.isopen())
    {
        /* Render here */
        
        gray_screen();
        shape.setRotation(controller.getRotation(), dims.refresh_rate);
        
        camera.update();
        shape.draw();
        controller.handleEvents();
        window.swap();

    }

    glfwTerminate();

    return 0;
}