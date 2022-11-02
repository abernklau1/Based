#include "bsdpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

#include "stb_image.h"

namespace Based {
OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) {
  int width, height, channels;
  stbi_set_flip_vertically_on_load(1);
  stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  BSD_CORE_ASSERT(data, "Failed to load image!");
  m_Width = width;
  m_Height = height;

  GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4) {
      internalFormat = GL_RGBA8;
      dataFormat = GL_RGBA;
    }
    else if (channels == 3) {
      internalFormat = GL_RGB8;
      dataFormat = GL_RGB;
    }

  BSD_CORE_ASSERT(internalFormat & dataFormat, "Format not supported");

  glGenTextures(1, &m_TextureID);
  glBindTexture(GL_TEXTURE_2D, m_TextureID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);

}

OpenGLTexture2D::~OpenGLTexture2D() {
  glDeleteTextures(1, &m_TextureID);
}

void OpenGLTexture2D::Bind(uint32_t slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_TextureID);
}
}
