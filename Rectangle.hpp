#ifndef OPENGL_RECTANGLE_HPP
#define OPENGL_RECTANGLE_HPP

#include <vector>

#include "Object.hpp"

class Rectangle : public Object {
private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    constexpr static
    const char uniform[] = "ourColor";

public:
    explicit
    Rectangle(const Shader *) noexcept;

    void Draw() const noexcept override;

    static
    void ColorUpdate(GLuint) noexcept;
};

#endif //OPENGL_RECTANGLE_HPP
