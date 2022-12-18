#include <Based.h>
#include <Based/Core/EntryPoint.h>

// #include "ExampleLayer.h"
#include "Sandbox2D/Sandbox2D.h"

class Sandbox : public Based::Application
{
    public:
        Sandbox()
        {
            // PushLayer(new ExampleLayer());
            PushLayer( new Sandbox2D() );
        }

        ~Sandbox() { }
};

Based::Application* Based::CreateApplication() { return new Sandbox(); }
