
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>


using namespace std;

const char* get_vertex_shader (){
    return "#version 460 core\n"
           "layout(location = 0) in vec3 vp;"
           "out vec4 vertexColor;"
           "void main(){"
           "   gl_Position = vec4(vp, 1.0);"
           "   vertexColor = vec4(0.5, 0.0, 0.5, 1.0);"
           "}"; 
}

const char* get_fragment_shader(){
    return  "#version 460 core\n"
            "out vec4 frag_color;"
            "in vec4 vertexColor;"
            "void main() {"
            "   frag_color = vertexColor;"
            "}";
}


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

static unsigned int create_shader(unsigned int shader_type, const char* source){

    GLint Result = GL_FALSE;
    int InfoLogLength;
    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0){
        vector<char> ShaderError(InfoLogLength + 1);
        glGetShaderInfoLog(shader, InfoLogLength, NULL, &ShaderError[0]);
        printf("%s\n", &ShaderError[0] );
    }

    return shader;
}

static GLuint create_program(){

    GLuint vs, fs, shader_program;
    GLint Result = GL_FALSE;
	int InfoLogLength;
    char const * gl_vertex_shader = get_vertex_shader();
    char const * gl_fragment_shader = get_fragment_shader();
    
    vs = create_shader(GL_VERTEX_SHADER, gl_vertex_shader);
    fs = create_shader(GL_FRAGMENT_SHADER, gl_fragment_shader);
    

    shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &Result);
	glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
        vector<char> errMessage(InfoLogLength + 1);
		glGetProgramInfoLog(shader_program, InfoLogLength, NULL, &errMessage[0]);
        printf("%s\n", &errMessage[0]);
	}

    return shader_program;
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

    GLFWwindow* window;
    GLFWmonitor* monitor;
    ScreenDim dims;
    GLuint vbo, vao, shader_program;

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
    shader_program = create_program();


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        
        gray_screen();

        glUseProgram(shader_program);

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    
        full_screen(window, monitor, &dims);

        glfwSwapBuffers(window);

    }

    glfwTerminate();

    return 0;
}