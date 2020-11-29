#version 460 core
out vec4 frag_color;
in vec4 vertexColor;
void main() {
    frag_color = vertexColor;
}