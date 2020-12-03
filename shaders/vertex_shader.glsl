#version 460 core
layout(location = 0) in vec3 vp;
out vec4 vertexColor;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;


void main(){
    gl_Position = projection * view * model * vec4(vp, 1.0);
    vertexColor = vec4(vp, 1.0);
}