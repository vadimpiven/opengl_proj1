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

    glUniformMatrix4fv(modelHandler, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(placementHandler, 1, GL_FALSE, glm::value_ptr(*placement));
    glUniformMatrix4fv(viewHandler, 1, GL_FALSE, glm::value_ptr(*view));
    glUniformMatrix4fv(projectionHandler, 1, GL_FALSE, glm::value_ptr(*projection));
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
          model(glm::mat4(1.0f)), modelHandler(),
          placement(placement), placementHandler(0),
          view(view), viewHandler(0),
          projection(projection), projectionHandler(0) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    modelHandler = shader->GetUniform("model");
    placementHandler = shader->GetUniform("placement");
    viewHandler = shader->GetUniform("view");
    projectionHandler = shader->GetUniform("projection");
}

Object::~Object() noexcept {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
