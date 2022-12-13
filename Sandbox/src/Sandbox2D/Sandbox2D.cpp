#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {

  m_CheckerboardTexture =
      Based::Texture2D::Create("Sandbox/assets/textures/Checkerboard.png");

  m_Particle.ColorBegin = {254/255.0f, 212/255.0f, 123/255.0f, 1.0f};
  m_Particle.ColorEnd = {254/255.0f, 109/255.0f, 41/255.0f, 1.0f};
  m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
  m_Particle.LifeTime = 1.0f;
  m_Particle.Velocity = {0.0f, 0.0f};
  m_Particle.VelocityVariation = {3.0f, 1.0f};
  m_Particle.Position = {0.0f, 0.0f};
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Based::Timestep ts) {
  BSD_PROFILE_FUNCTION();

  // Update
  m_CameraController.OnUpdate(ts);

  // Renderer
  // Reset Stats Here
  Based::Renderer2D::ResetStats();

  {
    BSD_PROFILE_SCOPE("Renderer Prep");
    Based::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Based::RenderCommand::Clear();
  }

  static float rotation = 0.0f;
  rotation += ts * 20.0f;

  Based::Renderer2D::BeginScene(m_CameraController.GetCamera());
  Based::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f},
                              {0.8f, 0.3f, 0.2f, 1.0f});
  Based::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f},
                              m_CheckerboardTexture, 1.0f);
  Based::Renderer2D::DrawQuad({-1.0f, -1.0f}, {1.0f, 1.0f},
                              {0.3f, 0.2f, 0.8f, 1.0f});

  Based::Renderer2D::DrawRotatedQuad({-2.f, -0.5f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotation), m_CheckerboardTexture, 20.0f);
  Based::Renderer2D::EndScene();

  Based::Renderer2D::BeginScene(m_CameraController.GetCamera());
  for (float y = -5.0; y < 5.0f; y+= 0.5f) {
    for (float x = -5.0f; x < 5.0f; x+= 0.5f) {
      glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f};
      Based::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
    }
  }
  Based::Renderer2D::EndScene();

  if (Based::Input::IsMouseButtonPressed(BSD_MOUSE_BUTTON_LEFT)) {
    auto [x, y] = Based::Input::GetMousePos();
    auto width = Based::Application::Get().GetWindow().GetWidth();
    auto height = Based::Application::Get().GetWindow().GetHeight();

    auto bounds = m_CameraController.GetBounds();
    auto pos = m_CameraController.GetCamera().GetPosition();
    x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
    y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
    m_Particle.Position = {x + pos.x, y + pos.y};
      for (int i = 0; i < 5; i++)
      m_ParticleSystem.Emit(m_Particle);
  }

  m_ParticleSystem.OnUpdate(ts);
  m_ParticleSystem.OnRender(m_CameraController.GetCamera());
}

void Sandbox2D::OnImGuiRender() {
  BSD_PROFILE_FUNCTION();

  ImGui::Begin("Settings");

  auto stats = Based::Renderer2D::GetStats();
  // ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
  ImGui::Text("Renderer2D Stats:");
  ImGui::Text("Draw Calls: %d", stats.DrawCalls);
  ImGui::Text("Quad Count: %d", stats.QuadCount);
  ImGui::Text("Total Vertex Count: %d", stats.GetTotalVertexCount());
  ImGui::Text("Total Index Count: %d", stats.GetTotalIndexCount());
  ImGui::End();
}

void Sandbox2D::OnEvent(Based::Event &e) { m_CameraController.OnEvent(e); }
