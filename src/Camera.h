#ifndef CAMERA_H
#define CAMERA_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Camera {
    public: 

        glm::mat4 view;
        glm::mat4 projection;
        unsigned int uniformProjection;
        unsigned int uniformView;

        Camera(int width ,int height);
        void  setUniforms(unsigned int uniformProj, unsigned int uniformView);
        void  setRotation(float* input, int speed);
        void  update();

};
#endif 