#version 330 core

out vec4 color;

uniform float ourColor;

void main() {
    color = vec4(ourColor, ourColor, 0, 1);
}
