#include <vector>
#include <array>

#include "Window.hpp"
#include "Camera.hpp"
#include "Error.hpp"
#include "Cone.hpp"

struct objectStorage {
    glm::mat4 placement;
    Object *object;
};

const GLsizei WIDTH = 800, HEIGHT = 600;
glm::mat4 VIEW, PROJECTION;
std::vector<Shader *> SH;
std::vector<objectStorage *> OBJ;
Camera *CAMERA;
std::array<bool, 1024> KEYS;

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    static bool firstMouse = true;
    static GLfloat lastX = 400, lastY = 300;
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    CAMERA->ProcessMouseMovement(xpos - lastX, lastY - ypos);

    lastX = xpos;
    lastY = ypos;
}

void keyCallback(GLFWwindow *window, GLint key, GLint, GLint action, GLint) noexcept {
    // close window on ESCAPE key press
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    } else if (key >= 0 && key < 1024) {
        if(action == GLFW_PRESS)
            KEYS[key] = true;
        else if(action == GLFW_RELEASE)
            KEYS[key] = false;
    }
}

void DoMovement(const GLfloat delta) {
    if(KEYS[GLFW_KEY_W])
        CAMERA->ProcessKeyboard(CameraMovement::FORWARD, delta);
    if(KEYS[GLFW_KEY_S])
        CAMERA->ProcessKeyboard(CameraMovement::BACKWARD, delta);
    if(KEYS[GLFW_KEY_A])
        CAMERA->ProcessKeyboard(CameraMovement::LEFT, delta);
    if(KEYS[GLFW_KEY_D])
        CAMERA->ProcessKeyboard(CameraMovement::RIGHT, delta);
    if(KEYS[GLFW_KEY_SPACE])
        CAMERA->ProcessKeyboard(CameraMovement::UP, delta);
    if(KEYS[GLFW_KEY_LEFT_SHIFT])
        CAMERA->ProcessKeyboard(CameraMovement::DOWN, delta);
}

void redraw(const GLfloat time, const GLfloat delta) noexcept {
    // move camera
    DoMovement(delta);
    VIEW = CAMERA->GetViewMatrix();

    // clear window with given color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // draw everything
    for (const auto &o: OBJ) { o->object->Draw(time, delta); }
    glCheckErrors();
}

int main() {
    // create window
    Window w(WIDTH, HEIGHT, "OpenGL Project One"); // create new window
    PROJECTION = glm::perspective(45.0f, (float) WIDTH / (float) HEIGHT, 0.1f, 1000.0f);
    CAMERA = new Camera();
    VIEW = CAMERA->GetViewMatrix();
    w.SetKeyCallback(keyCallback);
    w.SetCursorPosCallback(mouseCallback);

    // initialise shaders
    SH.resize(1);
    SH[0] = new Shader(VERT_CONE, FRAG_CONE);


    glm::mat4 placement;
    // initialise objects
    placement = glm::translate(
            glm::mat4(1.0),
            glm::vec3(0.0f, -0.15f, -1.5f)); // move back and down
    placement = glm::rotate(
            placement, 0.5f,
            glm::vec3(1.0, 0.0, 0.0)); // tilt front
    OBJ.emplace_back(new objectStorage);
    OBJ.back()->placement = placement;
    OBJ.back()->object = new Cone(SH[0], &(OBJ.back()->placement), &VIEW, &PROJECTION);

    // main loop
    w.Loop(redraw); // infinite loop while window is open

    // clear resources
    for (const auto &o: OBJ) {
        delete o->object;
        delete o;
    }
    for (const auto &s: SH) { delete s; }

    w.Destroy();
    return 0;
}
