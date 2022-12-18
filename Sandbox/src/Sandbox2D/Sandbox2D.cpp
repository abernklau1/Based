#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer( "Sandbox2D" ), m_CameraController( 1280.0f / 720.0f ) { }

void Sandbox2D::OnAttach()
{

    BSD_PROFILE_FUNCTION();

    m_CheckerboardTexture = Based::Texture2D::Create( "Sandbox/assets/textures/Checkerboard.png" );
}

void Sandbox2D::OnDetach() { }

void Sandbox2D::OnUpdate( Based::Timestep ts )
{
    BSD_PROFILE_FUNCTION();

    // Update
    m_CameraController.OnUpdate( ts );

    // Renderer
    // Reset Stats Here
    Based::Renderer2D::ResetStats();

    {
        BSD_PROFILE_SCOPE( "Renderer Prep" );
        Based::RenderCommand::SetClearColor( { 0.1f, 0.1f, 0.1f, 1 } );
        Based::RenderCommand::Clear();
    }

    static float rotation = 0.0f;
    rotation += ts * 20.0f;

    Based::Renderer2D::BeginScene( m_CameraController.GetCamera() );
    Based::Renderer2D::DrawQuad( { 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.3f, 0.2f, 1.0f } );
    Based::Renderer2D::DrawQuad( { 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 1.0f );
    Based::Renderer2D::DrawQuad( { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 0.3f, 0.2f, 0.8f, 1.0f } );

    Based::Renderer2D::DrawRotatedQuad( { -2.f, -0.5f, 0.0f },
                                        { 1.0f, 1.0f },
                                        glm::radians( rotation ),
                                        m_CheckerboardTexture,
                                        20.0f );
    Based::Renderer2D::EndScene();

    Based::Renderer2D::BeginScene( m_CameraController.GetCamera() );
    for ( float y = -5.0; y < 5.0f; y += 0.5f )
    {
        for ( float x = -5.0f; x < 5.0f; x += 0.5f )
        {
            glm::vec4 color = { ( x + 5.0f ) / 10.0f, 0.4f, ( y + 5.0f ) / 10.0f, 1.0f };
            Based::Renderer2D::DrawQuad( { x, y }, { 0.45f, 0.45f }, color );
        }
    }
    Based::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    BSD_PROFILE_FUNCTION();

    ImGui::Begin( "Settings" );
    auto stats = Based::Renderer2D::GetStats();
    ImGui::Text( "Renderer2D Stats:" );
    ImGui::Text( "Draw Calls: %d", stats.DrawCalls );
    ImGui::Text( "Quad Count: %d", stats.QuadCount );
    ImGui::Text( "Total Vertex Count: %d", stats.GetTotalVertexCount() );
    ImGui::Text( "Total Index Count: %d", stats.GetTotalIndexCount() );

    ImGui::End();
}

void Sandbox2D::OnEvent( Based::Event& e ) { m_CameraController.OnEvent( e ); }
