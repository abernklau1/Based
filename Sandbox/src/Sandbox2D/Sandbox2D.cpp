// #include "Sandbox2D.h"

// #include "imgui/imgui.h"

// #include <glm/ext/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

// Sandbox2D::Sandbox2D()
//     : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

// void Sandbox2D::OnAttach() {

//   m_CheckerboardTexture =
//       Based::Texture2D::Create("assets/textures/Checkerboard.png");
// }

// void Sandbox2D::OnDetach() {}

// void Sandbox2D::OnUpdate(Based::Timestep ts) {
//   // Update
//   m_CameraController.OnUpdate(ts);

//   // Renderer
//   Based::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
//   Based::RenderCommand::Clear();

//   Based::Renderer2D::BeginScene(m_CameraController.GetCamera());
//   Based::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f},
//                               {0.8f, 0.2f, 0.3f, 1.0f});
//   Based::Renderer2D::EndScene();
// }

// void Sandbox2D::OnImGuiRender() {
//   ImGui::Begin("Settings");
//   ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
//   ImGui::End();
// }

// void Sandbox2D::OnEvent(Based::Event &e) { m_CameraController.OnEvent(e); }
