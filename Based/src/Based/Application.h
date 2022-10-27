#pragma once

#include "Based/Events/ApplicationEvent.h"
#include "Based/Events/Event.h"
#include "Based/LayerStack.h"
#include "Core.h"
#include "Window.h"

#include "Based/ImGui/ImGuiLayer.h"

#include "Renderer/OrthographicCamera.h"


namespace Based {
class Application {
public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event &e);

  void PushLayer(Layer *layer);
  void PushOverlay(Layer *layer);

  inline Window &GetWindow() { return *m_Window; }

  inline static Application &Get() { return *s_Instance; }

private:
  bool OnWindowClose(WindowCloseEvent &e);

  std::unique_ptr<Window> m_Window;
  ImGuiLayer *m_ImGuiLayer;
  bool m_Running = true;
  LayerStack m_LayerStack;

private:
  static Application *s_Instance;
};

// To be defined in client

Application *CreateApplication();
} // namespace Based
