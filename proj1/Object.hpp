#ifndef OPENGL_OBJECT_HPP
#define OPENGL_OBJECT_HPP

#include <vector>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.hpp"
#include <GL/glew.h>

class Object {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    const Shader *const shader;

protected:
    glm::mat4 model;
    GLint modelHandler;
    glm::mat4 view;
    GLint viewHandler;
    glm::mat4 projection;
    GLint projectionHandler;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    void constructorBegin() const noexcept;

    void constructorEnd() const noexcept;

    void drawBegin() const noexcept;

    void drawEnd() const noexcept;

public:
    Object() = delete;

    explicit
    Object(const Shader *, glm::mat4) noexcept;

    virtual
    void Draw() noexcept = 0;

    virtual
    ~Object() noexcept;
};

#endif //OPENGL_OBJECT_HPP
