#include <vector>

#include "Window.hpp"
#include "Error.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"

std::vector<Object *> obj;

/// Is called whenever a key is pressed/released
void keyCallback(GLFWwindow *window, GLint key, GLint, GLint action, GLint) noexcept {
    // close window on ESCAPE key press
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

/// Is called whenever some user action happened and image have to be updated
void redraw() noexcept {
    // TODO: move camera and update viewport on user actions

    // clear window with given color
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glCheckErrors();

    // draw everything
    for (const auto &o: obj) { o->Draw(); }
    glCheckErrors();
}

int main() {
    // create window
    Window w(800, 600, "OpenGL Project One"); // create new window
    w.SetKeyCallback(keyCallback); // set user input processor

    // initialise objects
    obj.emplace_back(new Triangle(new Shader(VERT_VEC3ARR, FRAG_ORANGE)));
    obj.emplace_back(new Rectangle(new Shader(VERT_VEC3ARR, FRAG_YELLOW)));

    // main loop
    w.Loop(redraw); // infinite loop while window is opened

    // clear resources
    for (const auto &o: obj) { delete o; }
    w.Destroy();
    return 0;
}
