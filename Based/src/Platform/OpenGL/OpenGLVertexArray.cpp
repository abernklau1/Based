#include "OpenGLVertexArray.h"
#include "bsdpch.h"

#include <glad/glad.h>

namespace Based {

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
  case Based::ShaderDataType::None:
    return 0;
  case Based::ShaderDataType::Float:
    return GL_FLOAT;
  case Based::ShaderDataType::Float2:
    return GL_FLOAT;
  case Based::ShaderDataType::Float3:
    return GL_FLOAT;
  case Based::ShaderDataType::Float4:
    return GL_FLOAT;
  case Based::ShaderDataType::Mat3:
    return GL_FLOAT;
  case Based::ShaderDataType::Mat4:
    return GL_FLOAT;
  case Based::ShaderDataType::Int:
    return GL_INT;
  case Based::ShaderDataType::Int2:
    return GL_INT;
  case Based::ShaderDataType::Int3:
    return GL_INT;
  case Based::ShaderDataType::Int4:
    return GL_INT;
  case Based::ShaderDataType::Bool:
    return GL_BOOL;
  }

  BSD_CORE_ASSERT(false, "Unknown ShaderDataType");
  return 0;
}

OpenGLVertexArray::OpenGLVertexArray() {
  glGenVertexArrays(1, &m_VertexArrayID);
}

OpenGLVertexArray::~OpenGLVertexArray() {
  glDeleteVertexArrays(1, &m_VertexArrayID);
}

void OpenGLVertexArray::Bind() const { glBindVertexArray(m_VertexArrayID); }

void OpenGLVertexArray::Unbind() const { glBindVertexArray(0); }

void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {

  BSD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
                  "VertexBuffer has no layout!");
  glBindVertexArray(m_VertexArrayID);
  vertexBuffer->Bind();

  uint32_t index = 0;
  const auto &layout = vertexBuffer->GetLayout();
  for (const auto &element : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, element.GetComponentCount(),
                          ShaderDataTypeToOpenGLBaseType(element.Type),
                          element.Normalized ? GL_TRUE : GL_FALSE,
                          layout.GetStride(), (const void *)element.Offset);
    index++;
  }

  m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {
  glBindVertexArray(m_VertexArrayID);
  indexBuffer->Bind();

  m_IndexBuffer = indexBuffer;
}
} // namespace Based
