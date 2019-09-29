#include "Triangle.hpp"

Triangle::Triangle(GLuint shaderProgram) noexcept : Object(shaderProgram) {
    // init data
    vertices = {
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.0, 0.5, 0.0,
    };
    indices = {
            0, 1, 2,
    };

    // bind buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // load vertices
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    // say how to interpret them
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
    glEnableVertexAttribArray(0);

    // unbind buffers
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Triangle::Draw() const noexcept {
    // bind
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // draw
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // unbind
    glBindVertexArray(0);
    glUseProgram(0);
}