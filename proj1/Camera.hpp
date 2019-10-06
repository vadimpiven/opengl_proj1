#ifndef OPENGL_CAMERA_HPP
#define OPENGL_CAMERA_HPP

#include "GL/glew.h"
#include "glm.hpp"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    void updateCameraVectors() noexcept;

public:
    explicit
    Camera(glm::vec3 = glm::vec3(0.0f),
           glm::vec3 = glm::vec3(0.0f, 1.0f, 0.0f),
           GLfloat = -90.0f, GLfloat = 0.0f) noexcept;

    [[nodiscard]]
    glm::mat4 GetViewMatrix() const noexcept;

    void ProcessKeyboard(CameraMovement, GLfloat) noexcept;

    void ProcessMouseMovement(GLfloat, GLfloat, GLboolean = true) noexcept;
};

#endif //OPENGL_CAMERA_HPP
