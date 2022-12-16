#include "Renderer/Camera.h"
#include "Events/Event.h"
#include "Logs/Log.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
        UpdateViewProjectionMatrix();
    }

    void Camera::UpdateView() {
        m_ViewMatrix = glm::lookAt(
            glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
        UpdateViewProjectionMatrix();
    }

    void Camera::UpdateViewProjectionMatrix() {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::OnUpdate() {}
    void Camera::OnEvent(Event &e) {}

}