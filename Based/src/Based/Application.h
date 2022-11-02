#pragma once

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Core.h"
#include "Window.h"

#include "ImGui/ImGuiLayer.h"

#include "Renderer/OrthographicCamera.h"

#include "Core/Timestep.h"


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

private:

  Scope<Window> m_Window;
  ImGuiLayer *m_ImGuiLayer;
  bool m_Running = true;
  LayerStack m_LayerStack;
  float m_LastFrameTime = 0.0f;
private:
  static Application *s_Instance;
};

// To be defined in client

Application *CreateApplication();
} // namespace Based
