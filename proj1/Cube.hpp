#ifndef OPENGL_CUBE_HPP
#define OPENGL_CUBE_HPP

#include "Object.hpp"

class Cube : public Object {
    GLuint texture;

public:
    explicit
    Cube(const Shader *, const glm::mat4 *,
         const glm::mat4 *, const glm::mat4 *) noexcept;

    void Draw(GLfloat) noexcept override;

    ~Cube() override;
};

#endif //OPENGL_CUBE_HPP
