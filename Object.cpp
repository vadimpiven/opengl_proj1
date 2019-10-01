#include "Object.hpp"

void Object::constructorBind() const noexcept {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Object::constructorUnbind() noexcept {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::drawBind() const noexcept {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
}

void Object::drawUnbind() noexcept {
    glBindVertexArray(0);
    glUseProgram(0);
}

Object::Object(GLuint shaderProgram) noexcept : VAO(0), VBO(0), EBO(0), shaderProgram(shaderProgram) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
}

Object::~Object() noexcept {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}
