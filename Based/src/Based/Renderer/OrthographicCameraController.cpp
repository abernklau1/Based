#include "bsdpch.h"
#include "OrthographicCameraController.h"

#include "Based/Core/Input.h"
#include "Based/Core/KeyCodes.h"
namespace Based {

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation) {

}

void OrthographicCameraController::OnUpdate(Timestep ts) {

    if (Input::IsKeyPressed(BSD_KEY_A))
      m_CameraPosition.x -= m_CameraTranslationSpeed * ts;

    else if (Input::IsKeyPressed(BSD_KEY_D))
      m_CameraPosition.x += m_CameraTranslationSpeed * ts;

    if (Input::IsKeyPressed(BSD_KEY_W))
      m_CameraPosition.y += m_CameraTranslationSpeed * ts;

    else if (Input::IsKeyPressed(BSD_KEY_S))
      m_CameraPosition.y -= m_CameraTranslationSpeed * ts;


    if (m_Rotation) {

      if (Input::IsKeyPressed(BSD_KEY_Q))
        m_CameraRotation -= m_CameraRotationSpeed * ts;

      if (Input::IsKeyPressed(BSD_KEY_E))
        m_CameraRotation += m_CameraRotationSpeed * ts;

      m_Camera.SetRotation(m_CameraRotation);
    }

  m_Camera.SetPosition(m_CameraPosition);
  m_CameraTranslationSpeed = m_ZoomLevel;
}

void OrthographicCameraController::OnEvent(Event& e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<MouseScrolledEvent>(BSD_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
  dispatcher.Dispatch<WindowResizeEvent>(BSD_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
  m_ZoomLevel -= e.GetYOffset();
  m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
  return false;
}

bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e) {
  m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
  m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
  return false;
}
}
