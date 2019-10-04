#ifndef OPENGL_OBJECT_HPP
#define OPENGL_OBJECT_HPP

#include <vector>

#include "Shader.hpp"
#include <GL/glew.h>

class Object {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    const Shader *const shader;

protected:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    void constructorBegin() const noexcept;

    void constructorEnd() const noexcept;

    void drawBegin() const noexcept;

    void drawEnd() const noexcept;

public:
    Object() = delete;

    explicit
    Object(const Shader *) noexcept;

    virtual
    void Draw() noexcept = 0;

    virtual
    ~Object() noexcept;
};

#endif //OPENGL_OBJECT_HPP
