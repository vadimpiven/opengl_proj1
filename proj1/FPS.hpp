#ifndef OPENGL_FPS_HPP
#define OPENGL_FPS_HPP

#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <GL/glew.h>

#include "Shader.hpp"

class FPS {
    GLuint VAO;
    GLuint VBO;

    GLuint texture;

    const Shader *const shader;

    std::vector<GLfloat> vertices;

    void loadTexture() noexcept(false);

public:
    FPS() = delete;

    explicit
    FPS(const Shader *, GLsizei, GLsizei) noexcept;

    void Resize(GLsizei, GLsizei) noexcept;

    virtual
    void Draw(GLfloat) noexcept;

    virtual
    ~FPS() noexcept;
};

#endif //OPENGL_FPS_HPP
