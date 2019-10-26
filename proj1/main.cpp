#include <vector>
#include <array>

#include "Window.hpp"
#include "Camera.hpp"
#include "Error.hpp"
#include "Cone.hpp"
#include "Cube.hpp"
#include "FPS.hpp"

struct objectStorage {
    glm::mat4 placement;
    Object *object;
};

GLsizei WIDTH = 800, HEIGHT = 600;
glm::mat4 VIEW, PROJECTION;
std::vector<Shader *> SH;
std::vector<objectStorage *> OBJ;
FPS *fps;
Camera *CAMERA;
std::array<bool, 1024> KEYS;
std::array<bool, 8> MOUSE;

void windowCallback(GLFWwindow *window, int, int) {
    glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
}

void mouseCallback(GLFWwindow *, int button, int action, int) {
    if (button >= 0 && button < 8) {
        if (action == GLFW_PRESS) {
            MOUSE[button] = true;
        } else if (action == GLFW_RELEASE) {
            MOUSE[button] = false;
        }
    }
}

void cursorCallback(GLFWwindow *window, double xpos, double ypos) {
    static bool firstMouse = true;
    static GLfloat lastX = 400, lastY = 300;
    static GLFWcursor *cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

    if (MOUSE[GLFW_MOUSE_BUTTON_LEFT]) {
        if (firstMouse) {
            lastX = (GLfloat) xpos;
            lastY = (GLfloat) ypos;
            firstMouse = false;
            glfwSetCursor(window, cursor);
        }

        CAMERA->ProcessMouseMovement((GLfloat) xpos - lastX, lastY - (GLfloat) ypos);

        lastX = (GLfloat) xpos;
        lastY = (GLfloat) ypos;
    } else if (!firstMouse) {
        firstMouse = true;
        glfwSetCursor(window, nullptr);
    }
}

void keyCallback(GLFWwindow *window, GLint key, GLint, GLint action, GLint) noexcept {
    // close window on ESCAPE key press
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    } else if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            KEYS[key] = true;
        } else if (action == GLFW_RELEASE) {
            KEYS[key] = false;
        }
    }
}

void moveCamera(const GLfloat delta) {
    if (KEYS[GLFW_KEY_W]) {
        CAMERA->ProcessKeyboard(CameraMovement::FORWARD, delta);
    }
    if (KEYS[GLFW_KEY_S]) {
        CAMERA->ProcessKeyboard(CameraMovement::BACKWARD, delta);
    }
    if (KEYS[GLFW_KEY_A]) {
        CAMERA->ProcessKeyboard(CameraMovement::LEFT, delta);
    }
    if (KEYS[GLFW_KEY_D]) {
        CAMERA->ProcessKeyboard(CameraMovement::RIGHT, delta);
    }
    if (KEYS[GLFW_KEY_SPACE]) {
        CAMERA->ProcessKeyboard(CameraMovement::UP, delta);
    }
    if (KEYS[GLFW_KEY_LEFT_SHIFT]) {
        CAMERA->ProcessKeyboard(CameraMovement::DOWN, delta);
    }
}

void redraw(const GLfloat delta) noexcept {
    glViewport(0, 0, WIDTH, HEIGHT);
    PROJECTION = glm::perspective(45.0f, (float) WIDTH / (float) HEIGHT, 0.1f, 1000.0f);
    fps->Resize(WIDTH, HEIGHT);

    // move camera
    moveCamera(delta);
    VIEW = CAMERA->GetViewMatrix();

    // clear window with given color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(static_cast<GLbitfield>(GL_COLOR_BUFFER_BIT) |
            static_cast<GLbitfield>(GL_DEPTH_BUFFER_BIT) | static_cast<GLbitfield>(GL_STENCIL_BUFFER_BIT));

    // draw everything
    for (const auto &o: OBJ) { o->object->Draw(delta); }
    fps->Draw(delta);
    glCheckErrors();
}

int main() {
    // create window
    Window w(&WIDTH, &HEIGHT, "OpenGL Project One"); // create new window
    PROJECTION = glm::perspective(45.0f, (float) WIDTH / (float) HEIGHT, 0.1f, 1000.0f);
    CAMERA = new Camera();
    VIEW = CAMERA->GetViewMatrix();
    w.SetWindowSizeCallback(windowCallback);
    w.SetKeyCallback(keyCallback);
    w.SetMouseButtonCallback(mouseCallback);
    w.SetCursorPosCallback(cursorCallback);

    // initialise shaders
    SH.resize(3);
    SH[0] = new Shader(VERT_SKYBOX, FRAG_SKYBOX);
    SH[1] = new Shader(VERT_XYZ_RGB, FRAG_RGB);
    SH[2] = new Shader(VERT_FPS, FRAG_FPS);

    // initialise objects
    glm::mat4 placement;

    // cube skybox
    placement = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f));
    OBJ.emplace_back(new objectStorage);
    OBJ.back()->placement = placement;
    OBJ.back()->object = new Cube(SH[0], &(OBJ.back()->placement), &VIEW, &PROJECTION);

    // cone object
    placement = glm::translate(
            glm::mat4(1.0),
            glm::vec3(0.0f, -0.15f, -1.5f)); // move back and down
    placement = glm::rotate(
            placement, 0.5f,
            glm::vec3(1.0, 0.0, 0.0)); // tilt front
    OBJ.emplace_back(new objectStorage);
    OBJ.back()->placement = placement;
    OBJ.back()->object = new Cone(SH[1], &(OBJ.back()->placement), &VIEW, &PROJECTION);

    // fps display
    fps = new FPS(SH[2], WIDTH, HEIGHT);

    // main loop
    w.Loop(redraw); // infinite loop while window is open

    // clear resources
    for (const auto &o: OBJ) {
        delete o->object;
        delete o;
    }
    delete fps;
    for (const auto &s: SH) { delete s; }

    w.Destroy();
    return 0;
}
