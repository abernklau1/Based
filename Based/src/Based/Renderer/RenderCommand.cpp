#include "bsdpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Based {
RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
