#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Based {
VertexArray* VertexArray::Create() {
  switch(Renderer::GetAPI()) {
    case RendererAPI::API::None: BSD_CORE_ASSERT(false, "RendererAPI::None is currently not supported by the Based Engine"); return nullptr;
    case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
  }

  BSD_CORE_ASSERT(false, "Unknown RendererAPI");
  return nullptr;
}
}
