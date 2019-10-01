#include "Triangle.hpp"

Triangle::Triangle(const Shader * const shaderProgram) noexcept : Object(shaderProgram) {
    // init data
    vertices = {
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.0, 0.5, 0.0,
    };

    constructorBind();

    // load vertices
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    // say how to interpret them
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    constructorUnbind();
}

void Triangle::Draw() const noexcept {
    drawBind();

    // draw
    glDrawArrays(GL_TRIANGLES, 0, 3);

    drawUnbind();
}