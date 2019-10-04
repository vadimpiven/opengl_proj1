#version 330 core

in vec3 myColor;
out vec4 color;

void main() {
    color = vec4(myColor, 1.0f);
}