#include "Based/Renderer/RendererAPI.h"
#include "bsdpch.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Based
{
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
            case RendererAPI::API::None:
                BSD_CORE_ASSERT(false, "RendererAPI::None is currently not supported by the Based Engine");
                return nullptr;
            case RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
        }

        BSD_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
} // namespace Based
