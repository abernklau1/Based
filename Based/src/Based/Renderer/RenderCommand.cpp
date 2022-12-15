#include "Based/Renderer/RenderCommand.h"
#include "bsdpch.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Based
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
