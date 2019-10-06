#version 330 core

layout (location = 0) in vec3 inXYZ;
layout (location = 1) in vec3 inRGB;

out vec3 RGB;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(inXYZ, 1.0f);
    RGB = inRGB;
}
