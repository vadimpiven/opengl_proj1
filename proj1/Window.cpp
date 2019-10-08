#include <stdexcept>

#include "Window.hpp"

/// Clear resources and exit on error.
void Window::errorOccurred(const char err[]) noexcept(false) {
    glfwTerminate();
    throw std::runtime_error(err);
}

/// Initialise GLFW library to allow creating windows.
void Window::initGLFW() noexcept {
    glfwInit();

    // minimal OpenGL version 3.3, duplicated in CMakeList.txt
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // set profile for which a context will be created to core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // make window not resizable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // enable multisampling
    glfwWindowHint(GLFW_SAMPLES, 4);
}

/// Initialise GLEW library to allow interactions with OpenGL.
void Window::initGLEW() noexcept {
    glewExperimental = GL_TRUE; // for core profile support
    if (glewInit() != GLEW_OK) { errorOccurred("GLEW initialisation failed"); }
}

void Window::resizeWindow() noexcept {
    GLint width, height;
    glfwGetFramebufferSize(window, &width, &height); // get actual window size
    glViewport(0, 0, width, height); // set window position and size
    glEnable(GL_DEPTH_TEST); // enable depth check (for correct 3D redraw)
    glEnable(GL_STENCIL_TEST); // enable stencil check
    glEnable(GL_MULTISAMPLE); // enable multisampling
}

Window::Window(const GLsizei width, const GLsizei height, const char *title) noexcept {
    initGLFW(); // allows to create window
    glfwSwapInterval(1); // enable vertical synchronisation
    window = glfwCreateWindow(
            width, // WIDTH
            height, // height
            title, // title
            nullptr, // monitor where window is shown
            nullptr // window to share the context with
    );
    if (window == nullptr) { errorOccurred("Window creation failed"); }

    glfwMakeContextCurrent(window); // create context for window
    initGLEW(); // allows to use OpenGL
    resizeWindow();
}

void Window::SetWindowSizeCallback(GLFWwindowsizefun callback) noexcept {
    // make window resizable
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
    glfwSetWindowSizeCallback(window, callback); // listen for user actions
}

void Window::SetKeyCallback(GLFWkeyfun callback) noexcept {
    glfwSetKeyCallback(window, callback); // listen for user actions
}

void Window::SetMouseButtonCallback(GLFWmousebuttonfun callback) noexcept {
    glfwSetMouseButtonCallback(window, callback); // listen for user actions
}

void Window::SetCursorPosCallback(GLFWcursorposfun callback) noexcept {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // capture cursor
    glfwSetCursorPosCallback(window, callback); // listen for user actions
}

void Window::Loop(void(*redraw)(GLfloat, GLfloat)) noexcept {
    GLfloat deltaTime = 0.0f, lastFrame = 0.0f, currentFrame;

    while (!glfwWindowShouldClose(window)) { // while window is not closed
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents(); // check for user actions
        redraw(currentFrame, deltaTime); // update image
        glfwSwapBuffers(window); // show new image
    }
}

void Window::Destroy() noexcept {
    glfwDestroyWindow(window);
    glfwTerminate();
}
