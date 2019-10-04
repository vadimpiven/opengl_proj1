#ifndef OPENGL_TRIANGLE_HPP
#define OPENGL_TRIANGLE_HPP

#include "Object.hpp"

class Triangle : public Object {
public:
    explicit
    Triangle(const Shader *) noexcept;

    void Draw() noexcept override;
};

#endif //OPENGL_TRIANGLE_HPP
