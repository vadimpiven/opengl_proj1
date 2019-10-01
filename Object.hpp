#ifndef OPENGL_OBJECT_HPP
#define OPENGL_OBJECT_HPP

#include <GL/glew.h>

#include "Shaders.hpp"

class Object {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLuint shaderProgram;

protected:
    void constructorBind() const noexcept;

    static
    void constructorUnbind() noexcept;

    void drawBind() const noexcept;

    static
    void drawUnbind() noexcept;

public:
    Object() = delete;

    explicit
    Object(GLuint shaderProgram) noexcept;

    virtual
    void Draw() const noexcept = 0;

    virtual
    ~Object() noexcept;
};

#endif //OPENGL_OBJECT_HPP
