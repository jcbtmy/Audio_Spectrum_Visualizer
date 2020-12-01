#version 460 core
layout(location = 0) in vec3 vp;
out vec4 vertexColor;

uniform mat4 trans;

void main(){
    gl_Position = trans * vec4(vp, 1.0);
    vertexColor = vec4(vp, 1.0);
}