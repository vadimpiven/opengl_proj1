#ifndef OPENGL_CONE_HPP
#define OPENGL_CONE_HPP

#include "Object.hpp"

class Cone : public Object {
public:
    explicit
    Cone(const Shader *, glm::mat4) noexcept;

    void Draw() noexcept override;
};

#endif //OPENGL_CONE_HPP
