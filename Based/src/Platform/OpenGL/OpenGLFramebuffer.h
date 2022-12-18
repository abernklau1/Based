#pragma once
#include "Based/Renderer/Framebuffer.h"

namespace Based
{
    class OpenGLFramebuffer : public Framebuffer
    {
        public:
            OpenGLFramebuffer( const FramebufferSpecification& spec );
            virtual ~OpenGLFramebuffer();

            void Invalidate();

            void Bind() override;
            void Unbind() override;

            void Resize( uint32_t width, uint32_t height ) override;

            virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

            virtual uint32_t GetColorAttachmentRendererID() override { return m_ColorAttachment; }

        private:
            uint32_t m_FramebufferID   = 0;
            uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
            FramebufferSpecification m_Specification;
    };
} // namespace Based
