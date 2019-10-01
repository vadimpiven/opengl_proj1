#ifndef OPENGL_OBJECT_HPP
#define OPENGL_OBJECT_HPP

#include <GL/glew.h>

#include "Shader.hpp"

class Object {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    const Shader *const shader;

protected:
    void constructorBind() const noexcept;

    void constructorUnbind() const noexcept;

    void drawBind() const noexcept;

    void drawUnbind() const noexcept;

public:
    Object() = delete;

    explicit
    Object(const Shader *) noexcept;

    virtual
    void Draw() const noexcept = 0;

    virtual
    ~Object() noexcept;
};

#endif //OPENGL_OBJECT_HPP
