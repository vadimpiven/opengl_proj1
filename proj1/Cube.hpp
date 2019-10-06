#ifndef OPENGL_CUBE_HPP
#define OPENGL_CUBE_HPP

#include "Object.hpp"

class Cube : public Object {
public:
    explicit
    Cube(const Shader *, const glm::mat4 *,
         const glm::mat4 *, const glm::mat4 *) noexcept;

    void Draw(GLfloat, GLfloat) noexcept override;
};

#endif //OPENGL_CUBE_HPP
