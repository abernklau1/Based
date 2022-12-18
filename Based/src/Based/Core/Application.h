#pragma once

#include "Based/Core/Base.h"
#include "Based/Core/LayerStack.h"
#include "Based/Core/Window.h"
#include "Based/Events/ApplicationEvent.h"
#include "Based/Events/Event.h"

#include "Based/ImGui/ImGuiLayer.h"

#include "Based/Core/Timestep.h"

int main( int argc, char** argv );

namespace Based
{
    class Application
    {
        public:
            Application( const std::string& name = "Based App" );
            virtual ~Application();

            void OnEvent( Event& e );

            void PushLayer( Layer* layer );
            void PushOverlay( Layer* layer );

            Window& GetWindow() { return *m_Window; }

            void Close();

            static Application& Get() { return *s_Instance; }

        private:
            void Run();
            bool OnWindowClose( WindowCloseEvent& e );
            bool OnWindowResize( WindowResizeEvent& e );

        private:
            Scope<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running  = true;
            bool m_Minimize = false;
            LayerStack m_LayerStack;
            float m_LastFrameTime = 0.0f;

        private:
            static Application* s_Instance;
            friend int ::main( int argc, char** argv );
    };

    // To be defined in client

    Application* CreateApplication();
} // namespace Based
