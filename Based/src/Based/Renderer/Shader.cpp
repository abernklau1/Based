#include "Shader.h"
#include "bsdpch.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Based {
Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
  switch(Renderer::GetAPI()) {
    case RendererAPI::API::None: BSD_CORE_ASSERT(false, "RendererAPI::None is currently not supported by the Based Engine"); return nullptr;
    case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
  }

  BSD_CORE_ASSERT(false, "Unknown RendererAPI");
  return nullptr;
}
}
