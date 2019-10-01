#ifndef OPENGL_SHADER_HPP
#define OPENGL_SHADER_HPP

#include <vector>
#include <GL/glew.h>

class Shader {
    GLuint program;

    static
    GLuint vertexShader(const GLchar[]) noexcept(false);

    static
    GLuint fragmentShader(const GLchar[]) noexcept(false);

    static
    GLuint shaderProgram(GLuint, GLuint) noexcept(false);

public:
    Shader() = delete;

    Shader(const Shader&) = delete;

    explicit
    Shader(const GLchar[], const GLchar[]) noexcept(false);

    void Bind() const noexcept;

    void Unbind() const noexcept;

    virtual
    ~Shader() noexcept;
};

const GLchar FRAG_ORANGE[] = R"~(
#version 330 core

out vec4 color;

void main() {
    color = vec4(1, 0.5, 0.2, 1);
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

const GLchar FRAG_YELLOW[] = R"~(
#version 330 core

out vec4 color;

void main() {
    color = vec4(1, 1, 0, 1);
}
)~";

#endif //OPENGL_SHADER_HPP
