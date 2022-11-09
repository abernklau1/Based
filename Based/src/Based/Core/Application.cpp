#include "Application.h"
#include "Based/Core/Log.h"
#include "bsdpch.h"

#include "Based/Renderer/Renderer.h"

#include "Input.h"

#include "GLFW/glfw3.h"

namespace Based {

Application *Application::s_Instance = nullptr;

Application::Application() {
  BSD_CORE_ASSERT(s_Instance, "Application already exists");

  s_Instance = this;

  m_Window = Scope<Window>(Window::Create());
  m_Window->SetEventCallback(BSD_BIND_EVENT_FN(Application::OnEvent));

  Renderer::Init();

  m_ImGuiLayer = new ImGuiLayer();
  PushOverlay(m_ImGuiLayer);
}

Application::~Application() {}

void Application::PushLayer(Layer *layer) {
  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
  m_LayerStack.PushOverlay(layer);
  layer->OnAttach();
}

void Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      BSD_BIND_EVENT_FN(Application::OnWindowClose));

  dispatcher.Dispatch<WindowResizeEvent>(BSD_BIND_EVENT_FN(Application::OnWindowResize));
  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {

    (*--it)->OnEvent(e);
    if (e.Handled)
      break;
  }
}

void Application::Run() {
  while (m_Running) {

    float time = (float)glfwGetTime(); // Platform::GetTime()
    Timestep timestep = time - m_LastFrameTime;
    m_LastFrameTime = time;


    if (!m_Minimize) {

      for (Layer *layer : m_LayerStack)
        layer->OnUpdate(timestep);
    }

    m_ImGuiLayer->Begin();
    for (Layer *layer : m_LayerStack)
      layer->OnImGuiRender();

    m_ImGuiLayer->End();

    m_Window->OnUpdate();
  }
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}


bool Application::OnWindowResize(WindowResizeEvent &e) {
  if (e.GetWidth() == 0 || e.GetHeight() == 0) {
    m_Minimize = true;
    return false;
  }
  m_Minimize = false;
  Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

  return false;
}

} // namespace Based
