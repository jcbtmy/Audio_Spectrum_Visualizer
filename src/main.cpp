#include <iostream>
#include <GL/freeglut.h>

using namespace std;

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}

int main(int argc, char* argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial1");

    InitializeGlutCallbacks();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutMainLoop();

    return 0;
}