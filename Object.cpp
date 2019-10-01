#include "Object.hpp"

void Object::constructorBegin() const noexcept {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Object::constructorEnd() const noexcept {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::drawBegin() const noexcept {
    shader->Bind();
    glBindVertexArray(VAO);
    for (auto &u : uniformList) { u.callback(u.handler); }
}

void Object::drawEnd() const noexcept {
    glBindVertexArray(0);
    shader->Unbind();
}

Object::Object(const Shader *const shader) noexcept : VAO(0), VBO(0), EBO(0), shader(shader) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

Object::~Object() noexcept {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Object::setUniformUpdater(const char *uniform, void (*callback)(GLuint)) noexcept(false) {
    for (auto &u : uniformList) {
        if (u.name == uniform) {
            u.callback = callback;
            return;
        }
    }
    const GLuint handler = shader->GetUniform(uniform);
    uniformList.emplace_back(UniformHolder{uniform, handler, callback});
}
