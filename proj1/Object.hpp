#ifndef OPENGL_OBJECT_HPP
#define OPENGL_OBJECT_HPP

#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <GL/glew.h>

#include "Shader.hpp"

class Object {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    const Shader *const shader;

    GLuint transformHandler;

    const glm::mat4 *const placement;
    const glm::mat4 *const view;
    const glm::mat4 *const projection;

protected:
    glm::mat4 model;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    void constructorBegin() const noexcept;

    void constructorEnd() const noexcept;

    void drawBegin() const noexcept;

    void drawEnd() const noexcept;

public:
    Object() = delete;

    explicit
    Object(const Shader *, const glm::mat4 *,
           const glm::mat4 *, const glm::mat4 *) noexcept;

    virtual
    void Draw(GLfloat) noexcept = 0;

    virtual
    ~Object() noexcept;
};

#endif //OPENGL_OBJECT_HPP
