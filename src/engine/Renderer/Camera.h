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

        void OnUpdate();
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

        const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4 &GetViewProjectionMatrix() const {
            return m_ViewProjectionMatrix;
        }

    private:
        void UpdateProjection();
        void UpdateView();
        void UpdateViewProjectionMatrix();

    private:
        float m_FoV = 45.0f;
        float m_AspectRatio = 1.0f;
        float m_NearClip = 0.1f;
        float m_FarClip = 1000.0f;

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;

        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_FocalPoint = {0.0f, 0.0f, 0.0f};

        float m_ViewportWidth = 1280, m_ViewportHeight = 720;
    };

}

#endif