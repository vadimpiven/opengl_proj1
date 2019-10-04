#ifndef OPENGL_RECTANGLE_HPP
#define OPENGL_RECTANGLE_HPP

#include "Object.hpp"

class Rectangle : public Object {
private:
    GLuint uniformHandler;

public:
    explicit
    Rectangle(const Shader *) noexcept;

    void Draw() noexcept override;
};

#endif //OPENGL_RECTANGLE_HPP
