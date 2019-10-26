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

const GLchar FRAG_FPS[] = R"~(
#version 330 core

out vec4 color;

in vec2 TexCoords;

uniform sampler2D ourTexture;

void main() {
    color = texture(ourTexture, TexCoords);
})~";

const GLchar VERT_FPS[] = R"~(
#version 330 core

layout (location = 0) in vec2 inXY;
layout (location = 1) in vec2 texXY;

out vec2 TexCoords;

void main() {
    gl_Position = vec4(inXY, 0.0f, 1.0f);
    TexCoords = texXY;
})~";

const GLchar FRAG_RGB[] = R"~(
#version 330 core

in vec3 RGB;

out vec4 color;

void main() {
    color = vec4(RGB, 1.0f);
})~";

const GLchar FRAG_SKYBOX[] = R"~(
#version 330 core

out vec4 color;

in vec3 TexCoords;

uniform samplerCube skybox;

void main() {
    color = texture(skybox, TexCoords);
})~";

const GLchar VERT_SKYBOX[] = R"~(
#version 330 core

layout (location = 0) in vec3 inXYZ;

out vec3 TexCoords;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(inXYZ, 1.0f);
    TexCoords = inXYZ;
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
