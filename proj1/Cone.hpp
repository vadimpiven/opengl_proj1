#ifndef OPENGL_CONE_HPP
#define OPENGL_CONE_HPP

#include <glm.hpp>

#include "Object.hpp"

class Cone : public Object {
    GLuint uniformHandler;

public:
    explicit
    Cone(const Shader *) noexcept;

    void Draw() noexcept override;
};

#endif //OPENGL_CONE_HPP
