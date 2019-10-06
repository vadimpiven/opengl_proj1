#include <cmath>

#include "Cone.hpp"

glm::dvec3 hsv2rgb(double angle) {
    double q, t;
    long long i;
    glm::dvec3 out;

    angle *= 3 / M_PI;
    i = static_cast<long long>(angle);
    t = angle - static_cast<double>(i);
    q = 1.0 - t;

    switch (i) {
    case 0:
        out.r = 1;
        out.g = t;
        out.b = 0;
        return out;
    case 1:
        out.r = q;
        out.g = 1;
        out.b = 0;
        return out;
    case 2:
        out.r = 0;
        out.g = 1;
        out.b = t;
        return out;
    case 3:
        out.r = 0;
        out.g = q;
        out.b = 1;
        return out;
    case 4:
        out.r = t;
        out.g = 0;
        out.b = 1;
        return out;
    default:
        out.r = 1;
        out.g = 0;
        out.b = q;
        return out;
    }
}

Cone::Cone(
        const Shader *const shaderProgram,
        const glm::mat4 *const placement,
        const glm::mat4 *const view,
        const glm::mat4 *const projection
) noexcept
        : Object(shaderProgram, placement, view, projection) {
    constructorBegin();

    const GLfloat h = 0.6, r = 0.5;
    const unsigned n = 60, s = 6;
    vertices.resize(s * (n + 2));
    indices.resize(3 * (n * 2));

    // cone top
    vertices[s * 0 + 0] = 0; // x
    vertices[s * 0 + 1] = -h; // y
    vertices[s * 0 + 2] = 0; // z
    vertices[s * 0 + 3] = 0; // r
    vertices[s * 0 + 4] = 0; // g
    vertices[s * 0 + 5] = 0; // b

    // cone base center
    vertices[s * 1 + 0] = 0;
    vertices[s * 1 + 1] = h;
    vertices[s * 1 + 2] = 0;
    vertices[s * 1 + 3] = 1;
    vertices[s * 1 + 4] = 1;
    vertices[s * 1 + 5] = 1;

    // first point
    vertices[s * 2 + 0] = r;
    vertices[s * 2 + 1] = h;
    vertices[s * 2 + 2] = 0;
    vertices[s * 2 + 3] = 1;
    vertices[s * 2 + 4] = 0;
    vertices[s * 2 + 5] = 0;

    float angle = (2 * M_PI) / n;
    unsigned j = 0;
    glm::dvec3 color;
    for (unsigned i = 3; i < n + 2; ++i) {
        color = hsv2rgb(angle);

        vertices[s * i + 0] = r * cos(angle);
        vertices[s * i + 1] = h;
        vertices[s * i + 2] = r * sin(angle);
        vertices[s * i + 3] = color.r;
        vertices[s * i + 4] = color.g;
        vertices[s * i + 5] = color.b;

        indices[j++] = 0;
        indices[j++] = i - 1;
        indices[j++] = i;

        indices[j++] = 1;
        indices[j++] = i - 1;
        indices[j++] = i;

        angle += (2 * M_PI) / n;
    }

    indices[j++] = 0;
    indices[j++] = 2;
    indices[j++] = n + 1;

    indices[j++] = 1;
    indices[j++] = 2;
    indices[j++] = n + 1;

    // load vertices
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    // say how to interpret them
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (GLvoid *) (0 * sizeof(vertices[0])));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (GLvoid *) (3 * sizeof(vertices[0])));
    glEnableVertexAttribArray(1);

    constructorEnd();
}

void Cone::Draw(const GLfloat time, GLfloat) noexcept {
    drawBegin();

    model = glm::rotate(glm::mat4(1.0f), time * -0.5f, glm::vec3(0.0, 1.0, 0.0));
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid *) (0 * sizeof(indices[0])));

    drawEnd();
}
