#ifndef OPENGL_TRIANGLE_HPP
#define OPENGL_TRIANGLE_HPP

#include <vector>

#include "Object.hpp"

class Triangle : public Object {
private:
    std::vector<GLfloat> vertices;

public:
    explicit
    Triangle(const Shader *) noexcept;

    void Draw() const noexcept override;
};

#endif //OPENGL_TRIANGLE_HPP
