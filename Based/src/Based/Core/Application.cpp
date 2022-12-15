#include "Based/Core/Application.h"
#include "Based/Core/Log.h"
#include "bsdpch.h"

#include "Based/Renderer/Renderer.h"

#include "Based/Core/Input.h"

#include <GLFW/glfw3.h>

namespace Based
{

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        BSD_PROFILE_FUNCTION();

        BSD_CORE_ASSERT(!s_Instance, "Application already exists");

        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback(BSD_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        BSD_PROFILE_FUNCTION();
        Renderer::Shutdown();
    }

    void Application::PushLayer(Layer* layer)
    {
        BSD_PROFILE_FUNCTION();
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        BSD_PROFILE_FUNCTION();
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        BSD_PROFILE_FUNCTION();
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BSD_BIND_EVENT_FN(Application::OnWindowClose));

        dispatcher.Dispatch<WindowResizeEvent>(BSD_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {

            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    void Application::Run()
    {
        BSD_PROFILE_FUNCTION();
        while (m_Running)
        {
            BSD_PROFILE_SCOPE("Engine Loop");

            float time        = (float)glfwGetTime(); // Platform::GetTime()
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime   = time;

            if (!m_Minimize)
            {
                {
                    BSD_PROFILE_SCOPE("Application LayerStack OnUpdate")
                    for (Layer* layer : m_LayerStack)
                        layer->OnUpdate(timestep);
                }
                m_ImGuiLayer->Begin();
                {
                    BSD_PROFILE_SCOPE("ImGui LayerStack OnUpdate")
                    for (Layer* layer : m_LayerStack)
                        layer->OnImGuiRender();
                }
                m_ImGuiLayer->End();
            }

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        BSD_PROFILE_FUNCTION();
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimize = true;
            return false;
        }
        m_Minimize = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

} // namespace Based
