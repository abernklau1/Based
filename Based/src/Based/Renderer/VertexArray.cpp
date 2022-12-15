#include "Based/Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace Based
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                BSD_CORE_ASSERT(false, "RendererAPI::None is currently not supported by the Based Engine");
                return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
        }

        BSD_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
} // namespace Based
