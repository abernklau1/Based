#include "bsdpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Based {
Ref<Texture2D> Texture2D::Create(const std::string& path) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None: BSD_CORE_ASSERT(false, "RendererAPI::None is currently not supported by the Based Engine"); return nullptr;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
  }

  BSD_CORE_ASSERT(false, "Unknown RendererAPI");
  return nullptr;
}
}
