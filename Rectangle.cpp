#include "Rectangle.hpp"

Rectangle::Rectangle(GLuint shaderProgram) noexcept : Object(shaderProgram) {
    // init data
    vertices = {
            0.8,  -0.5, 0.0,
            0.8, -0.8, 0.0,
            -0.8, -0.8, 0.0,
            -0.8, -0.5, 0.0
    };
    indices = {
            0, 1, 3,
            1, 2, 3,
    };

    // bind buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // load vertices
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    // say how to interpret them
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    // unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Rectangle::Draw() const noexcept {
    // bind
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // draw
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    // unbind
    glBindVertexArray(0);
    glUseProgram(0);
}