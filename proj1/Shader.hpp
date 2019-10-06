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

const GLchar FRAG_RGB[] = R"~(
#version 330 core

in vec3 RGB;

out vec4 color;

void main() {
    color = vec4(RGB, 1.0f);
})~";

const GLchar FRAG_WHITE[] = R"~(
#version 330 core

out vec4 color;

void main() {
    color = vec4(1.0f);
})~";

const GLchar VERT_XYZ[] = R"~(
#version 330 core

layout (location = 0) in vec3 inXYZ;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(inXYZ, 1.0f);
}
)~";

const GLchar VERT_XYZ_RGB[] = R"~(
#version 330 core

layout (location = 0) in vec3 inXYZ;
layout (location = 1) in vec3 inRGB;

out vec3 RGB;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(inXYZ, 1.0f);
    RGB = inRGB;
}
)~";

#endif //OPENGL_SHADER_HPP
