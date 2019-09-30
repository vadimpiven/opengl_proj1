#ifndef OPENGL_OBJECT_HPP
#define OPENGL_OBJECT_HPP

#include <GL/glew.h>

#include "Shaders.hpp"

class Object {
protected:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLuint shaderProgram;

public:
    Object() = delete;

    explicit
    Object(GLuint shaderProgram) noexcept : VAO(0), VBO(0), EBO(0), shaderProgram(shaderProgram) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    virtual
    void Draw() const noexcept = 0;

    virtual
    ~Object() noexcept {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(shaderProgram);
    }
};

#endif //OPENGL_OBJECT_HPP
