#version 330 core

layout (location = 0) in vec2 inXY;
layout (location = 1) in vec2 texXY;

out vec2 TexCoords;

void main() {
    gl_Position = vec4(inXY, 0.0f, 1.0f);
    TexCoords = texXY;
}