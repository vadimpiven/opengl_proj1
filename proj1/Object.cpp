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

    glm::mat4 transform = (*projection) * (*view) * (*placement) * model;
    glUniformMatrix4fv(transformHandler, 1, GL_FALSE, glm::value_ptr(transform));
}

void Object::drawEnd() const noexcept {
    glBindVertexArray(0);
    shader->Unbind();
}

Object::Object(
        const Shader *const shader,
        const glm::mat4 *const placement,
        const glm::mat4 *const view,
        const glm::mat4 *const projection
) noexcept
        : VAO(0), VBO(0), EBO(0), shader(shader),
          model(glm::mat4(1.0f)),
          placement(placement), view(view),
          projection(projection),
          transformHandler(0) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    transformHandler = shader->GetUniform("transform");
}

Object::~Object() noexcept {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
