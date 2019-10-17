#version 330 core

layout (location = 0) in vec3 inXYZ;

out vec3 TexCoords;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(inXYZ, 1.0f);
    TexCoords = inXYZ;
}
