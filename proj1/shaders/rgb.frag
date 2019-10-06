#version 330 core

in vec3 RGB;

out vec4 color;

void main() {
    color = vec4(RGB, 1.0f);
}