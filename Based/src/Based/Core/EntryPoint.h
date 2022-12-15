#pragma once
#include "Based/Core/Base.h"

extern Based::Application* Based::CreateApplication();

int main(int argc, char** argv)
{
    Based::Log::Init();

    BSD_PROFILE_BEGIN_SESSION("Startup", "BasedProfile-Startup.json");
    auto app = Based::CreateApplication();
    BSD_PROFILE_END_SESSION();

    BSD_PROFILE_BEGIN_SESSION("Runtime", "BasedProfile-Runtime.json");
    app->Run();
    BSD_PROFILE_END_SESSION();

    BSD_PROFILE_BEGIN_SESSION("Shutdown", "BasedProfile-Shutdown.json");
    delete app;
    BSD_PROFILE_END_SESSION();
}
