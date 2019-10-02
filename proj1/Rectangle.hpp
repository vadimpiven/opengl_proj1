#ifndef OPENGL_RECTANGLE_HPP
#define OPENGL_RECTANGLE_HPP

#include <vector>

#include "Object.hpp"

class Rectangle : public Object {
private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    GLuint uniformHandler;

public:
    explicit
    Rectangle(const Shader *) noexcept;

    void Draw() const noexcept override;
};

#endif //OPENGL_RECTANGLE_HPP
