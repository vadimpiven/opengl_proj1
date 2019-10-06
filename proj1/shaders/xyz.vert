#version 330 core

layout (location = 0) in vec3 inXYZ;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(inXYZ, 1.0f);
}
