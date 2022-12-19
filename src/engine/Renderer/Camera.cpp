#include "Renderer/Camera.h"
#include "Core/Input.h"
#include "Core/KeyCode.h"
#include "Core/MouseCode.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Logs/Log.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Hanabi {

    Camera::Camera() {
        UpdateProjection();
        UpdateView();
    }

    Camera::Camera(float fov, float aspectRatio, float nearClip, float farClip)
        : m_FoV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip) {

        UpdateProjection();
        UpdateView();
    }

    void Camera::UpdateProjection() {
        m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FoV), m_AspectRatio, m_NearClip, m_FarClip);
    }

    void Camera::UpdateView() {
        m_ViewMatrix = glm::lookAt(
            m_Position,                 // position vector
            m_Position + m_CameraFront, // target vector
            m_CameraUp                  // up vector
        );
    }

    void Camera::OnUpdate(float ts) {
        if (Input::IsKeyPressed(Key::W)) {
            m_Position += m_MoveSpeed * ts * m_CameraFront;
        }
        if (Input::IsKeyPressed(Key::S)) {
            m_Position -= m_MoveSpeed * ts * m_CameraFront;
        }
        UpdateView();
    }

    void Camera::OnEvent(Event &e) {}

}