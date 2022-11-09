#include "Platform/OpenGL/OpenGLBuffer.h"
#include "bsdpch.h"
#include "Buffer.h"
#include "Renderer.h"

namespace Based {

  VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size) {

    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None: BSD_CORE_ASSERT(false, "RendererAPI::None is currently not supported by the Based Engine"); return nullptr;
    case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
   }

    BSD_CORE_ASSERT(false, "Unknown renderer API");
    return nullptr;
}

  IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size) {

    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None: BSD_CORE_ASSERT(false, "RendererAPI::None is currently not supported by the Based Engine"); return nullptr;
    case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
    }

   BSD_CORE_ASSERT(false, "Unknown renderer API");
   return nullptr;
}
}
