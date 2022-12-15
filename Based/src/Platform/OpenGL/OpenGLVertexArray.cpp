#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "bsdpch.h"

#include <glad/glad.h>

namespace Based
{

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case Based::ShaderDataType::None: return 0;
            case Based::ShaderDataType::Float: return GL_FLOAT;
            case Based::ShaderDataType::Float2: return GL_FLOAT;
            case Based::ShaderDataType::Float3: return GL_FLOAT;
            case Based::ShaderDataType::Float4: return GL_FLOAT;
            case Based::ShaderDataType::Mat3: return GL_FLOAT;
            case Based::ShaderDataType::Mat4: return GL_FLOAT;
            case Based::ShaderDataType::Int: return GL_INT;
            case Based::ShaderDataType::Int2: return GL_INT;
            case Based::ShaderDataType::Int3: return GL_INT;
            case Based::ShaderDataType::Int4: return GL_INT;
            case Based::ShaderDataType::Bool: return GL_BOOL;
        }

        BSD_CORE_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        BSD_PROFILE_FUNCTION();
        glGenVertexArrays(1, &m_VertexArrayID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        BSD_PROFILE_FUNCTION();
        glDeleteVertexArrays(1, &m_VertexArrayID);
    }

    void OpenGLVertexArray::Bind() const
    {
        BSD_PROFILE_FUNCTION();
        glBindVertexArray(m_VertexArrayID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        BSD_PROFILE_FUNCTION();
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        BSD_PROFILE_FUNCTION();

        BSD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");
        glBindVertexArray(m_VertexArrayID);
        vertexBuffer->Bind();

        uint32_t index     = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            switch (element.Type)
            {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool:
                    {
                        glEnableVertexAttribArray(m_VertexBufferIndex);
                        glVertexAttribPointer(m_VertexBufferIndex, element.GetComponentCount(),
                                              ShaderDataTypeToOpenGLBaseType(element.Type),
                                              element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                                              (const void*)element.Offset);
                        m_VertexBufferIndex++;
                        break;
                    }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                    {
                        uint8_t count = element.GetComponentCount();
                        for (uint8_t i = 0; i < count; i++)
                        {
                            glEnableVertexAttribArray(m_VertexBufferIndex);
                            glVertexAttribPointer(m_VertexBufferIndex, count,
                                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                                  element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                                                  (const void*)(sizeof(float) * count * i));
                            glVertexAttribDivisor(m_VertexBufferIndex, 1);
                            m_VertexBufferIndex++;
                        }
                        break;
                    }
                default: BSD_CORE_ASSERT(false, "Unknown ShaderDataType");
            }
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_VertexArrayID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
} // namespace Based
