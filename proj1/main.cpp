#include <vector>

#include "Window.hpp"
#include "Error.hpp"
#include "Cone.hpp"

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  | GL_STENCIL_BUFFER_BIT);

    // draw everything
    for (const auto &o: obj) { o->Draw(); }
    glCheckErrors();
}

int main() {
    std::vector<Shader *> sh;

    // create window
    GLsizei width = 800, height = 600;
    Window w(width, height, "OpenGL Project One"); // create new window
    auto projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    w.SetKeyCallback(keyCallback); // set user input processor

    // initialise objects
    sh.emplace_back(new Shader(VERT_CONE, FRAG_CONE));
    obj.emplace_back(new Cone(sh.back(), projection));

    // main loop
    w.Loop(redraw); // infinite loop while window is open

    // clear resources
    for (const auto &o: obj) { delete o; }
    for (const auto &s: sh) { delete s; }

    w.Destroy();
    return 0;
}
