#include "OpenGLBuffer.h"
#include "bsdpch.h"
#include <glad/glad.h>

namespace Based {

// --- Vertex Buffer Creation ------------
OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
  BSD_PROFILE_FUNCTION();
  glGenBuffers(1, &m_VertexBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
  BSD_PROFILE_FUNCTION();
  glGenBuffers(1, &m_VertexBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
  BSD_PROFILE_FUNCTION();
  glDeleteBuffers(1, &m_VertexBufferID);
}

void OpenGLVertexBuffer::Bind() const {
  BSD_PROFILE_FUNCTION();
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
}

void OpenGLVertexBuffer::Unbind() const {
  BSD_PROFILE_FUNCTION();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void* data, uint32_t size) {
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

// --- Index Buffer Creation --------------

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count)
    : m_Count(count) {
  glGenBuffers(1, &m_IndexBufferID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices,
               GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
  glDeleteBuffers(1, &m_IndexBufferID);
}

void OpenGLIndexBuffer::Bind() const {

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
}

void OpenGLIndexBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Based
