#ifndef OPENGL_SHADERS_HPP
#define OPENGL_SHADERS_HPP

#include <vector>
#include <GL/glew.h>

GLuint VertexShader(const GLchar[]) noexcept(false);

GLuint FragmentShader(const GLchar shader[]) noexcept(false);

GLuint ShaderProgram(const std::vector<GLuint>&) noexcept(false);

const GLchar FRAG_ORANGE[] = R"~(
#version 330 core

out vec4 color;

void main() {
    color = vec4(1.0, 0.5, 0.2, 1.0);
}
)~";

const GLchar VERT_VEC3ARR[] = R"~(
#version 330 core

layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
)~";

#endif //OPENGL_SHADERS_HPP
