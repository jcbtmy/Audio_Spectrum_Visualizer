
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Shader.h"


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
    glClear(GL_COLOR_BUFFER_BIT);
}

static GLuint load_triangle(){

    GLuint VBO=0;

    GLfloat vertex_buffer_data[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(   GL_ARRAY_BUFFER, 
                    sizeof(vertex_buffer_data),
                    vertex_buffer_data,
                    GL_STATIC_DRAW);


    return VBO;
    
}

static GLuint create_VAO(GLuint VBO){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        NULL
    );

    return VAO;

}

static void full_screen(GLFWwindow* window, GLFWmonitor* monitor, ScreenDim* dims){

    static bool fullscreen = false;
    static bool last_key;

    glfwPollEvents();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
        return;
    }
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !last_key){
        if(!fullscreen) glfwSetWindowMonitor(window, monitor, 0,0, dims->width, dims->height, dims->refresh_rate);
        if(fullscreen) glfwSetWindowMonitor(window, NULL, 0 ,0 , dims->height/2, dims->width/2, dims->refresh_rate);
        fullscreen = !fullscreen;
        printf("width: %d || height: %d\n", dims->width ,dims->height);
    }
    last_key = glfwGetKey(window, GLFW_KEY_F);
}



int main(void){

    GLuint vbo, vao;
    GLFWwindow* window;
    GLFWmonitor* monitor;
    ScreenDim dims;


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    monitor = glfwGetPrimaryMonitor();
    get_resolution(&(dims.width), &(dims.height), &(dims.refresh_rate));
    vbo = load_triangle();
    vao = create_VAO(vbo);
    Shader shader("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        
        gray_screen();

        shader.use();

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    
        full_screen(window, monitor, &dims);

        glfwSwapBuffers(window);

    }

    glfwTerminate();

    return 0;
}