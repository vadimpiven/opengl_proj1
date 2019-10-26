#include <stdexcept>

#include "stb_image.h"
#include "FPS.hpp"

void FPS::loadTexture() noexcept(false) {
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("fps.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        stbi_image_free(data);
        throw std::runtime_error("unable to load skybox textures");
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

FPS::FPS(
        const Shader *const shaderProgram,
        const GLsizei width,
        const GLsizei height
) noexcept : VAO(0), VBO(0), shader(shaderProgram), texture(0) {
    const GLfloat px = 2.0f / static_cast<GLfloat>(width), py = 2.0f / static_cast<GLfloat>(height),
            x = 48.0f, y = 61.0f, p = 14.0f;
    vertices = {
            // 0
            -1.0f + (p + 0.f * x) * px, 1.0f - (p) * py, 0.f, 1.f,
            -1.0f + (p + 0.f * x) * px, 1.0f - (p + y) * py, 0.f, 0.f,
            -1.0f + (p + (0.f + 1.f) * x) * px, 1.0f - (p + y) * py, 0.1f, 0.f,

            -1.0f + (p + 0.f * x) * px, 1.0f - (p) * py, 0.f, 1.f,
            -1.0f + (p + (0.f + 1.f) * x) * px, 1.0f - (p) * py, 0.1f, 1.f,
            -1.0f + (p + (0.f + 1.f) * x) * px, 1.0f - (p + y) * py, 0.1f, 0.f,
            // 1
            -1.0f + (p + 1.f * x) * px, 1.0f - (p) * py, 0.f, 1.f,
            -1.0f + (p + 1.f * x) * px, 1.0f - (p + y) * py, 0.f, 0.f,
            -1.0f + (p + (1.f + 1.f) * x) * px, 1.0f - (p + y) * py, 0.1f, 0.f,

            -1.0f + (p + 1.f * x) * px, 1.0f - (p) * py, 0.f, 1.f,
            -1.0f + (p + (1.f + 1.f) * x) * px, 1.0f - (p) * py, 0.1f, 1.f,
            -1.0f + (p + (1.f + 1.f) * x) * px, 1.0f - (p + y) * py, 0.1f, 0.f,
            // 2
            -1.0f + (p + 2.f * x) * px, 1.0f - (p) * py, 0.f, 1.f,
            -1.0f + (p + 2.f * x) * px, 1.0f - (p + y) * py, 0.f, 0.f,
            -1.0f + (p + (2.f + 1.f) * x) * px, 1.0f - (p + y) * py, 0.1f, 0.f,

            -1.0f + (p + 2.f * x) * px, 1.0f - (p) * py, 0.f, 1.f,
            -1.0f + (p + (2.f + 1.f) * x) * px, 1.0f - (p) * py, 0.1f, 1.f,
            -1.0f + (p + (2.f + 1.f) * x) * px, 1.0f - (p + y) * py, 0.1f, 0.f,
    };

    glGenTextures(1, &texture);
    loadTexture();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(vertices[0]), (GLvoid * )(0 * sizeof(vertices[0])));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(vertices[0]), (GLvoid * )(2 * sizeof(vertices[0])));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void FPS::Resize(const GLsizei width, const GLsizei height) noexcept {
    const GLfloat px = 2.0f / static_cast<GLfloat>(width), py = 2.0f / static_cast<GLfloat>(height),
            x = 48.0f, y = 61.0f, p = 14.0f;

    for (unsigned char i = 0; i < 3; ++i) {
        vertices[0 + (6 * i + 0) * 4] = vertices[0 + (6 * i + 1) * 4] = vertices[0 + (6 * i + 3) * 4] =
                -1.0f + (p + static_cast<GLfloat>(i) * x) * px;
        vertices[0 + (6 * i + 2) * 4] = vertices[0 + (6 * i + 4) * 4] = vertices[0 + (6 * i + 5) * 4] =
                -1.0f + (p + (static_cast<GLfloat>(i) + 1.f) * x) * px;
        vertices[1 + (6 * i + 0) * 4] = vertices[1 + (6 * i + 3) * 4] = vertices[1 + (6 * i + 4) * 4] =
                1.0f - (p) * py;
        vertices[1 + (6 * i + 1) * 4] = vertices[1 + (6 * i + 2) * 4] = vertices[1 + (6 * i + 5) * 4] =
                1.0f - (p + y) * py;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0 * sizeof(vertices[0]), vertices.size() * sizeof(vertices[0]), &vertices[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void FPS::Draw(const GLfloat delta) noexcept {
    static GLfloat time = 0;
    static int fps = 0;
    time += delta;
    ++fps;
    if (time > 1.0f) {
        for (int i = 2, d = fps % 10; i >= 0; --i, fps /= 10, d = fps % 10) {
            vertices[2 + (6 * i + 0) * 4] = vertices[2 + (6 * i + 1) * 4] = vertices[2 + (6 * i + 3) * 4] =
                    static_cast<GLfloat>(d) * 0.1f + 0.0f;
            vertices[2 + (6 * i + 2) * 4] = vertices[2 + (6 * i + 4) * 4] = vertices[2 + (6 * i + 5) * 4] =
                    static_cast<GLfloat>(d) * 0.1f + 0.1f;
        }

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0 * sizeof(vertices[0]), vertices.size() * sizeof(vertices[0]), &vertices[0]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        time = 0;
        fps = 0;
    }

    shader->Bind();
    glBindVertexArray(VAO);

    glDepthMask(GL_FALSE);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindTexture(GL_TEXTURE_2D, 0);
    glDepthMask(GL_TRUE);

    glBindVertexArray(0);
    shader->Unbind();
}

FPS::~FPS() noexcept {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texture);
}
