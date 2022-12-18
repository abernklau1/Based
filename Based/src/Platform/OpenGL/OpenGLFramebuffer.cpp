#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Based/Renderer/Framebuffer.h"
#include "bsdpch.h"

#include <glad/glad.h>

namespace Based
{
    OpenGLFramebuffer::OpenGLFramebuffer( const FramebufferSpecification& spec ) : m_Specification( spec ) { Invalidate(); }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers( 1, &m_FramebufferID );
        glDeleteTextures( 1, &m_ColorAttachment );
        glDeleteTextures( 1, &m_DepthAttachment );
    }

    void OpenGLFramebuffer::Invalidate()
    {
        if ( m_FramebufferID )
        {
            glDeleteFramebuffers( 1, &m_FramebufferID );
            glDeleteTextures( 1, &m_ColorAttachment );
            glDeleteTextures( 1, &m_DepthAttachment );
        }

        glGenFramebuffers( 1, &m_FramebufferID );
        glBindFramebuffer( GL_FRAMEBUFFER, m_FramebufferID );
        glGenTextures( 1, &m_ColorAttachment );
        glBindTexture( GL_TEXTURE_2D, m_ColorAttachment );
        glTexImage2D( GL_TEXTURE_2D,
                      0,
                      GL_RGBA8,
                      m_Specification.Width,
                      m_Specification.Height,
                      0,
                      GL_RGBA,
                      GL_UNSIGNED_BYTE,
                      nullptr );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0 );

        glGenTextures( 1, &m_DepthAttachment );
        glBindTexture( GL_TEXTURE_2D, m_DepthAttachment );
        glTexImage2D( GL_TEXTURE_2D,
                      0,
                      GL_DEPTH24_STENCIL8,
                      m_Specification.Width,
                      m_Specification.Height,
                      0,
                      GL_DEPTH_STENCIL,
                      GL_UNSIGNED_INT_24_8,
                      NULL );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0 );

        BSD_CORE_ASSERT( glCheckFramebufferStatus( GL_FRAMEBUFFER ) == GL_FRAMEBUFFER_COMPLETE,
                         "Framebuffer is incomplete" );

        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer( GL_FRAMEBUFFER, m_FramebufferID );
#ifdef BSD_PLATFORM_WINDOWS
        glViewport( 0, 0, m_Specification.Width, m_Specification.Height );
#endif
    }

    void OpenGLFramebuffer::Unbind() { glBindFramebuffer( GL_FRAMEBUFFER, 0 ); }

    void OpenGLFramebuffer::Resize( uint32_t width, uint32_t height )
    {
        m_Specification.Width  = width;
        m_Specification.Height = height;
        Invalidate();
    }

} // namespace Based