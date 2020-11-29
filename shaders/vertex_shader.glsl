#version 460 core
layout(location = 0) in vec3 vp;
out vec4 vertexColor;
void main(){
    gl_Position = vec4(vp, 1.0);
    vertexColor = vec4(0.5, 0.0, 0.5, 1.0);
}