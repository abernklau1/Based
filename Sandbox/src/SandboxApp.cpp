#include "Based.h"

#include "Based/Events/KeyEvent.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp>   // glm::vec3
#include <glm/vec4.hpp>   // glm::vec4
glm::mat4 camera(float Translate, glm::vec2 const &Rotate) {
  glm::mat4 Projection =
      glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
  glm::mat4 View =
      glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
  View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
  View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
  return Projection * View * Model;
}

class ExampleLayer : public Based::Layer {
public:
  ExampleLayer() : Layer("Example") { auto cam = camera(5.0f, {0.5f, 0.5f}); }

  void OnUpdate() override {
    if (Based::Input::IsKeyPressed(BSD_KEY_TAB))
      BSD_TRACE("Tab key has been pressed");
  }

  void OnImGuiRender() override {
    ImGui::Begin("Test");
    ImGui::Text("Hello World");
    ImGui::End();
  }

  void OnEvent(Based::Event &event) override {
    if (event.GetEventType() == Based::EventType::KeyPressed) {
      Based::KeyPressedEvent &e = (Based::KeyPressedEvent &)event;
      BSD_TRACE("{0}", e.GetKeyCode());
    }
  }
};

class Sandbox : public Based::Application {
public:
  Sandbox() { PushLayer(new ExampleLayer()); }

  ~Sandbox() {}
};

Based::Application *Based::CreateApplication() { return new Sandbox(); }
