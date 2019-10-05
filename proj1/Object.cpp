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
    if (modelHandler != -1) {
        glUniformMatrix4fv(modelHandler, 1, GL_FALSE, glm::value_ptr(model));
    }
    if (viewHandler != -1) {
        glUniformMatrix4fv(viewHandler, 1, GL_FALSE, glm::value_ptr(view));
    }
    if (projectionHandler != -1) {
        glUniformMatrix4fv(projectionHandler, 1, GL_FALSE, glm::value_ptr(projection));
    }
}

void Object::drawEnd() const noexcept {
    glBindVertexArray(0);
    shader->Unbind();
}

Object::Object(const Shader *const shader, const glm::mat4 projection) noexcept
        : VAO(0), VBO(0), EBO(0), shader(shader),
          model(glm::mat4(1.0f)), modelHandler(-1),
          view(glm::mat4(1.0f)), viewHandler(-1),
          projection(projection), projectionHandler(-1) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    try {
        modelHandler = shader->GetUniform("model");
    } catch(...) { modelHandler = -1; }
    try {
        viewHandler = shader->GetUniform("view");
    } catch(...) { viewHandler = -1; }
    try {
        projectionHandler = shader->GetUniform("projection");
    } catch(...) { projectionHandler = -1; }
}

Object::~Object() noexcept {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
