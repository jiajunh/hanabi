#pragma once
#ifndef HANABI_CAMERA_H
#define HANABI_CAMERA_H

#include "Events/Event.h"

#include <glm/glm.hpp>

namespace Hanabi {

    class Camera {
    public:
        Camera();
        Camera(float fov, float aspectRatio, float nearClip, float farClip);

        ~Camera() = default;

        void OnUpdate(float ts);
        void OnEvent(Event &e);

        inline void SetViewportSize(float width, float height) {
            m_ViewportWidth = width;
            m_ViewportHeight = height;
            UpdateProjection();
        }

        inline void SetFoV(float fov) {
            m_FoV = fov;
            UpdateProjection();
        }

        inline void SetPosition(float x, float y, float z) {
            m_Position = glm::vec3(x, y, z);
            UpdateView();
        }

        inline void SetMoveSpeed(float speed) { m_MoveSpeed = speed; }
        inline void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }

        const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
        glm::mat4 GetViewProjectionMatrix() const {
            return m_ProjectionMatrix * m_ViewMatrix;
        }

        float GetPitch() const { return m_Pitch; }
        float GetYaw() const { return m_Yaw; }
        float GetMoveSpeed() const { return m_Pitch; }
        float GetRotationSpeed() const { return m_Yaw; }

    private:
        void UpdateProjection();
        void UpdateView();

    private:
        float m_FoV = 45.0f;
        float m_AspectRatio = 1.0f;
        float m_NearClip = 0.1f;
        float m_FarClip = 1000.0f;

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;

        glm::vec3 m_Position = {4.0f, 3.0f, 3.0f};
        glm::vec3 m_CameraFront = {-4.0f, -3.0f, -3.0f};
        glm::vec3 m_CameraUp = {0.0f, 1.0f, 0.0f};

        float m_ViewportWidth = 1280, m_ViewportHeight = 720;

        float m_Pitch = 0.0f, m_Yaw = -90.0f;

        float m_MoveSpeed = 1.0f, m_RotationSpeed = 1.0f;
    };

}

#endif