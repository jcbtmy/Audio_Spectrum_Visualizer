
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "Window.h"
#include "Shader.h"
#include "Shape.h"
#include "Controller.h"
#include "Camera.h"
#include "Audio.h"

#define STACKS 32

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



int main(int argc, char* argv[]){

    GLFWmonitor* monitor;
    ScreenDim dims;
    unsigned long ticks = 0;
    unsigned int counter = 0;

    if(argc < 2)
    {
        std::cout << "Usage: ./Graphics <mp3 file>\n";
        exit(1);
    }
   

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    Window window(1080, 720, "Hello World");
    Controller controller(window.getContext());
    Audio audio;

    glewExperimental = GL_TRUE;
    glewInit();

    monitor = glfwGetPrimaryMonitor();
    get_resolution(&(dims.width), &(dims.height), &(dims.refresh_rate));

    Shader shader("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    Shape shape(STACKS);
    Camera camera(dims.width, dims.height);

    camera.setUniforms(shader.getUniform("projection"), shader.getUniform("view"));
    shape.setUniform(shader.getUniform("model"));
    audio.setAudioFile(argv[1]);
    audio.setAudioDevice();


    shape.useWireFrame(3.0f);
    shape.load();
    audio.setBinSize(STACKS);
    audio.start();

    while (window.isopen())
    {
        /* Render here */
        gray_screen();
        shader.use();
        shape.scaleStacks(counter++, audio.getFrequencies());
        shape.setRotation(controller.getRotation(), dims.refresh_rate);
        camera.update();
        shape.draw();
        controller.handleEvents();
        window.swap();

    }

    audio.stop();

    glfwTerminate();

    return 0;
}