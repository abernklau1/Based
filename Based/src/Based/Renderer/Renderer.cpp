#include "Based/Renderer/Renderer.h"
#include "Based/Renderer/Renderer2D.h"
#include "bsdpch.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Based
{

    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init()
    {
        BSD_PROFILE_FUNCTION();

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown() { Renderer2D::Shutdown(); }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
#ifdef BSD_PLATFORM_WINDOWS
        RenderCommand::SetViewport(0, 0, width, height);
#endif
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() { }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {

        shader->Bind();
        shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // namespace Based
