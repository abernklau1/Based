#include "bsdpch.h"
#include "Based/Renderer/RendererContext.h"

#include "Based/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Based {
Scope<RendererContext> RendererContext::Create(void *window) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None: BSD_CORE_ASSERT(false, "RendererAPI::None is not currently supported by the Based Engine"); return nullptr;
    case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
  }

  BSD_CORE_ASSERT(false, "Unknown RendererAPI");
  return nullptr;
}
}
