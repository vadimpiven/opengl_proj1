#include <stdexcept>

#include "Shader.hpp"
#include "Error.hpp"

GLuint Shader::vertexShader(const GLchar shader[]) noexcept(false) {
    // compile shader
    GLuint s = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s, 1, &shader, nullptr);
    glCompileShader(s);

    // check for error
    GLint success;
    glGetShaderiv(s, GL_COMPILE_STATUS, &success);
    if (success) { return s; }

    // get error message
    GLchar infoLog[512];
    glGetShaderInfoLog(s, 512, nullptr, infoLog);
    throw std::runtime_error(infoLog);
}

GLuint Shader::fragmentShader(const GLchar shader[]) noexcept(false) {
    // compile shader
    GLuint s = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s, 1, &shader, nullptr);
    glCompileShader(s);

    // check for error
    GLint success;
    glGetShaderiv(s, GL_COMPILE_STATUS, &success);
    if (success) { return s; }

    // get error message
    GLchar infoLog[512];
    glGetShaderInfoLog(s, 512, nullptr, infoLog);
    throw std::runtime_error(infoLog);
}

GLuint Shader::shaderProgram(const GLuint vShader, const GLuint fShader) noexcept(false) {
    // link program
    GLuint p = glCreateProgram();
    glAttachShader(p, vShader);
    glAttachShader(p, fShader);
    glLinkProgram(p);

    // check for error
    GLint success;
    glGetProgramiv(p, GL_LINK_STATUS, &success);
    if (success) {
        glDeleteShader(vShader);
        glDeleteShader(fShader);
        return p;
    }

    // get error message
    GLchar infoLog[512];
    glGetProgramInfoLog(p, 512, nullptr, infoLog);
    throw std::runtime_error(infoLog);
}

Shader::Shader(const GLchar vShader[], const GLchar fShader[]) noexcept(false) {
    const GLuint vs = vertexShader(vShader);
    const GLuint fs = fragmentShader(fShader);
    program = shaderProgram(vs, fs);
}

void Shader::Bind() const noexcept {
    glUseProgram(program);
    glCheckErrors();
}

void Shader::Unbind() const noexcept {
    glUseProgram(0);
}

Shader::~Shader() noexcept {
    glDeleteProgram(program);
}
