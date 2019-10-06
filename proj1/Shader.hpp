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

    Shader(const Shader &) = delete;

    explicit
    Shader(const GLchar[], const GLchar[]) noexcept(false);

    void Bind() const noexcept;

    void Unbind() const noexcept;

    GLuint GetUniform(const GLchar *) const noexcept(false);

    virtual
    ~Shader() noexcept;
};

const GLchar FRAG_CONE[] = R"~(
#version 330 core

in vec3 myColor;
out vec4 color;

void main() {
    color = vec4(myColor, 1.0f);
})~";

const GLchar VERT_CONE[] = R"~(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 myColor;

uniform mat4 model;
uniform mat4 placement;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * placement * model * vec4(position, 1.0f);
    myColor = color;
}
)~";

#endif //OPENGL_SHADER_HPP
