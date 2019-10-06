#include "Cube.hpp"

Cube::Cube(
        const Shader *const shaderProgram,
        const glm::mat4 *const placement,
        const glm::mat4 *const view,
        const glm::mat4 *const projection
) noexcept
        : Object(shaderProgram, placement, view, projection) {
    const GLfloat h = 0.5;
    vertices = {
            -h, h, -h,
            h, h, -h,
            h, h, h,
            -h, h, h,
            -h, -h, -h,
            h, -h, -h,
            h, -h, h,
            -h, -h, h
    };
    indices = {
            0, 1, 2,
            0, 3, 2,
            0, 4, 5,
            0, 1, 5,
            0, 4, 7,
            0, 3, 7,
            1, 5, 6,
            1, 2, 6,
            2, 3, 7,
            2, 6, 7,
            4, 5, 6,
            4, 7, 6
    };
    model = glm::rotate(glm::mat4(1.0f), -6.7f, glm::vec3(0.0f, 1.0f, 0.0f));

    constructorBegin();

    // load vertices
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    // say how to interpret them
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vertices[0]), (GLvoid *) (0 * sizeof(vertices[0])));
    glEnableVertexAttribArray(0);

    constructorEnd();
}

void Cube::Draw(const GLfloat time, GLfloat) noexcept {
    drawBegin();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid *) (0 * sizeof(indices[0])));

    drawEnd();
}
