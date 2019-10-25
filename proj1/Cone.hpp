#ifndef OPENGL_CONE_HPP
#define OPENGL_CONE_HPP

#include "Object.hpp"

class Cone : public Object {
public:
    explicit
    Cone(const Shader *, const glm::mat4 *,
         const glm::mat4 *, const glm::mat4 *) noexcept;

    void Draw(GLfloat) noexcept override;
};

#endif //OPENGL_CONE_HPP
