#pragma once

#include "Based/Events/ApplicationEvent.h"
#include "Based/Events/Event.h"
#include "Based/Core/LayerStack.h"
#include "Based/Core/Core.h"
#include "Based/Core/Window.h"

#include "Based/ImGui/ImGuiLayer.h"

#include "Based/Renderer/OrthographicCamera.h"

#include "Based/Core/Timestep.h"


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
  bool OnWindowResize(WindowResizeEvent &e);
private:

  Scope<Window> m_Window;
  ImGuiLayer *m_ImGuiLayer;
  bool m_Running = true;
  bool m_Minimize = false;
  LayerStack m_LayerStack;
  float m_LastFrameTime = 0.0f;
private:
  static Application *s_Instance;
};

// To be defined in client

Application *CreateApplication();
} // namespace Based
