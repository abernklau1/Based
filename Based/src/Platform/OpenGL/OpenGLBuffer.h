#pragma once
#include "bsdpch.h"
#include "Based/Renderer/Buffer.h"

namespace Based {
class OpenGLVertexBuffer: public VertexBuffer {

public:
  OpenGLVertexBuffer(float *vertices, uint32_t size);
  virtual ~OpenGLVertexBuffer();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout;}
  virtual const BufferLayout& GetLayout() const override { return m_Layout; }

private:
  uint32_t m_VertexBufferID;
  BufferLayout m_Layout;
};

class OpenGLIndexBuffer: public IndexBuffer {

public:
  OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
  virtual ~OpenGLIndexBuffer();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual uint32_t GetCount() const override { return m_Count; }

private:
  uint32_t m_IndexBufferID;
  uint32_t m_Count;
};
}
