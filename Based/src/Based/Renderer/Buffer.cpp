#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"
#include "bsdpch.h"

namespace Based {

Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {

  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    BSD_CORE_ASSERT(
        false,
        "RendererAPI::None is currently not supported by the Based Engine");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return CreateRef<OpenGLVertexBuffer>(size);
  }

  BSD_CORE_ASSERT(false, "Unknown renderer API");
  return nullptr;
}

Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size) {

  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    BSD_CORE_ASSERT(
        false,
        "RendererAPI::None is currently not supported by the Based Engine");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return CreateRef<OpenGLVertexBuffer>(vertices, size);
  }

  BSD_CORE_ASSERT(false, "Unknown renderer API");
  return nullptr;
}

Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count) {

  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    BSD_CORE_ASSERT(
        false,
        "RendererAPI::None is currently not supported by the Based Engine");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return  CreateRef<OpenGLIndexBuffer>(indices, count);
  }

  BSD_CORE_ASSERT(false, "Unknown renderer API");
  return nullptr;
}
} // namespace Based
