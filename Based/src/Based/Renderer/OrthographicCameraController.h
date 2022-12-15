#pragma once

#include "Based/Core/Timestep.h"
#include "Based/Events/ApplicationEvent.h"
#include "Based/Events/MouseEvent.h"
#include "Based/Renderer/OrthographicCamera.h"

namespace Based
{

    struct OrthographicCameraBounds
    {
            float Left, Right;
            float Bottom, Top;

            float GetWidth() { return Right - Left; }

            float GetHeight() { return Top - Bottom; }
    };

    class OrthographicCameraController
    {
        public:
            OrthographicCameraController(float aspectRation, bool rotation = false);
            void OnUpdate(Timestep ts);
            void OnEvent(Event& e);

            OrthographicCamera& GetCamera() { return m_Camera; }

            const OrthographicCamera& GetCamera() const { return m_Camera; }

            float GetZoomLevel() const { return m_ZoomLevel; }

            void SetZoomLevel(float level) { m_ZoomLevel = level; }

            const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

        private:
            bool OnMouseScrolled(MouseScrolledEvent& e);
            bool OnWindowResize(WindowResizeEvent& e);

        private:
            float m_AspectRatio;
            float m_ZoomLevel = 1.0f;
            OrthographicCameraBounds m_Bounds;
            OrthographicCamera m_Camera;

            bool m_Rotation;

            glm::vec3 m_CameraPosition     = {0.0f, 0.0f, 0.0f};
            float m_CameraRotation         = 0.0f;
            float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 1.0f;
    };
} // namespace Based
