#include "Based/Renderer/Shader.h"
#include "bsdpch.h"

#include "Based/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Based
{

    Ref<Shader> Shader::Create(const std::string& filePath)
    {

        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                BSD_CORE_ASSERT(false, "RendererAPI::None is currently not supported by the Based Engine");
                return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filePath);
        }

        BSD_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                BSD_CORE_ASSERT(false, "RendererAPI::None is currently not supported by the Based Engine");
                return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        BSD_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        BSD_CORE_ASSERT(!Exists(name), "Shader already exists");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    Based::Ref<Based::Shader> ShaderLibrary::Load(const std::string& filePath)
    {
        auto shader = Shader::Create(filePath);
        Add(shader);
        return shader;
    }

    Based::Ref<Based::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
    {
        auto shader = Shader::Create(filePath);
        Add(name, shader);
        return shader;
    }

    Based::Ref<Based::Shader> ShaderLibrary::Get(const std::string& name)
    {
        BSD_CORE_ASSERT(Exists(name), "Shader not found");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const { return m_Shaders.find(name) != m_Shaders.end(); }
} // namespace Based
