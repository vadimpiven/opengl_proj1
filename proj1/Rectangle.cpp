#include <cmath>

#include "Rectangle.hpp"
#include <GLFW/glfw3.h>

Rectangle::Rectangle(const Shader *const shaderProgram) noexcept : Object(shaderProgram) {
    constructorBegin();

    vertices = {
            0.8, -0.5, 0.0,
            0.8, -0.8, 0.0,
            -0.8, -0.8, 0.0,
            -0.8, -0.5, 0.0
    };
    indices = {
            0, 1, 3,
            1, 2, 3,
    };
    uniformHandler = shaderProgram->GetUniform("ourColor");

    // load vertices
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    // say how to interpret them
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vertices[0]), (GLvoid*)(0 * sizeof(vertices[0])));
    glEnableVertexAttribArray(0);

    constructorEnd();
}

void Rectangle::Draw() noexcept {
    drawBegin();

    GLfloat timeValue = glfwGetTime();
    GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
    glUniform1f(uniformHandler, greenValue);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid*)(0 * sizeof(indices[0])));

    drawEnd();
}
