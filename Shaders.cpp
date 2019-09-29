#include <stdexcept>

#include "Shaders.hpp"

GLuint VertexShader(const GLchar shader[]) noexcept(false) {
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

GLuint FragmentShader(const GLchar shader[]) noexcept(false) {
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

/// creates shader program and deletes shaders
GLuint ShaderProgram(const std::vector<GLuint>& shaders) noexcept(false) {
    // link program
    GLuint p = glCreateProgram();
    for (const auto s: shaders) { glAttachShader(p, s); }
    glLinkProgram(p);

    // check for error
    GLint success;
    glGetProgramiv(p, GL_LINK_STATUS, &success);
    if (success) {
        for (const auto s: shaders) { glDeleteShader(s); }
        return p;
    }

    // get error message
    GLchar infoLog[512];
    glGetProgramInfoLog(p, 512, nullptr, infoLog);
    throw std::runtime_error(infoLog);
}
