#pragma once

#include "Based/Renderer/Texture.h"

#include <glad/glad.h>

namespace Based
{
    class OpenGLTexture2D : public Texture2D
    {
        public:
            OpenGLTexture2D( uint32_t, uint32_t height );
            OpenGLTexture2D( const std::string& path );
            virtual ~OpenGLTexture2D();

            virtual void SetData( void* data, uint32_t size ) override;

            virtual uint32_t GetWidth() const override { return m_Width; }

            virtual uint32_t GetHeight() const override { return m_Height; }

            virtual uint32_t GetTextureID() const override { return m_TextureID; }

            virtual void Bind( uint32_t slot = 0 ) const override;

            virtual bool operator==( const Texture& other ) const override
            {
                return m_TextureID == ( (OpenGLTexture2D&)other ).m_TextureID;
            }

        private:
            std::string m_Path;

            uint32_t m_Width, m_Height;

            uint32_t m_TextureID;

            GLenum m_InternalFormat, m_DataFormat;
    };
} // namespace Based
