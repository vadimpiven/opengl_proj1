#ifndef OPENGL_OBJECT_HPP
#define OPENGL_OBJECT_HPP

#include <vector>

#include "Shader.hpp"
#include <GL/glew.h>

class Object {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    struct UniformHolder {
        const char *name;

        GLuint handler;

        void (*callback)(GLuint);
    };

    std::vector<UniformHolder> uniformList;

    const Shader *const shader;

protected:
    void constructorBegin() const noexcept;

    void constructorEnd() const noexcept;

    void drawBegin() const noexcept;

    void drawEnd() const noexcept;

    void setUniformUpdater(const char *, void(*)(GLuint)) noexcept(false);

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
