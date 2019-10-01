#include <stdexcept>

#include <GL/glew.h>

void glCheckErrors() noexcept(false) {
    switch (glGetError()) {
    case GL_NO_ERROR:
        return;
    case GL_INVALID_ENUM:
        throw std::runtime_error("GL_INVALID_ENUM");
    case GL_INVALID_VALUE:
        throw std::runtime_error("GL_INVALID_VALUE");
    case GL_INVALID_OPERATION:
        throw std::runtime_error("GL_INVALID_OPERATION");
    case GL_STACK_OVERFLOW:
        throw std::runtime_error("GL_STACK_OVERFLOW");
    case GL_STACK_UNDERFLOW:
        throw std::runtime_error("GL_STACK_UNDERFLOW");
    case GL_OUT_OF_MEMORY:
        throw std::runtime_error("GL_OUT_OF_MEMORY");
    default:
        throw std::runtime_error("GL unknown error");
    }
}
