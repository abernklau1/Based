#include "Based/Renderer/Framebuffer.h"
#include "bsdpch.h"

#include "Based/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Based
{
    Ref<Framebuffer> Framebuffer::Create( const FramebufferSpecification& spec )
    {
        switch ( Renderer::GetAPI() )
        {
            case RendererAPI::API::None:
                BSD_CORE_ASSERT( false, "RendererAPI::None is not supported by the Based Engine" )
                return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>( spec );
        }
        BSD_CORE_ASSERT( false, "Unknown RendererAPI" );
        return nullptr;
    }
} // namespace Based
