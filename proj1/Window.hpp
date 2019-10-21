#ifndef OPENGL_WINDOW_HPP
#define OPENGL_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
    GLFWwindow *window;

    static void errorOccurred(const char[]) noexcept(false);

    static void initGLFW() noexcept;

    static void initGLEW() noexcept;

    void resizeWindow(GLsizei *, GLsizei *) noexcept;

public:
    Window(GLsizei *, GLsizei *, const char *) noexcept;

    void SetWindowSizeCallback(GLFWwindowsizefun) noexcept;

    void SetKeyCallback(GLFWkeyfun) noexcept;

    void SetMouseButtonCallback(GLFWmousebuttonfun) noexcept;

    void SetCursorPosCallback(GLFWcursorposfun) noexcept;

    void Loop(void(*)(GLfloat, GLfloat)) noexcept;

    void Destroy() noexcept;
};

#endif //OPENGL_WINDOW_HPP
