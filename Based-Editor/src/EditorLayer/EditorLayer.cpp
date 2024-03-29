#include "EditorLayer.h"
#include "Based/Scene/Components.h"

#include <imgui/imgui.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Based
{

  EditorLayer::EditorLayer() : Layer( "EditorLayer" ), m_CameraController( 1280.0f / 720.0f ) { }

  void EditorLayer::OnAttach()
  {

    BSD_PROFILE_FUNCTION();

    m_CheckerboardTexture = Texture2D::Create( "Based-Editor/assets/textures/Checkerboard.png" );

    FramebufferSpecification spec;
    spec.Width  = 1280;
    spec.Height = 720;

    m_Framebuffer = Framebuffer::Create( spec );

    m_Scene = CreateRef<Scene>();

    // Entity
    auto square = m_Scene->CreateEntity();
    square.AddComponent<SpriteRendererComponent>( glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f ) );

    m_SquareEntity = square;
  }

  void EditorLayer::OnDetach() { }

  void EditorLayer::OnUpdate( Timestep ts )
  {
    BSD_PROFILE_FUNCTION();

    // Update
    if ( m_IsViewportFocused )
      m_CameraController.OnUpdate( ts );

    // Renderer
    // Reset Stats Here
    Renderer2D::ResetStats();

    m_Framebuffer->Bind();
    RenderCommand::SetClearColor( { 0.1f, 0.1f, 0.1f, 1 } );
    RenderCommand::Clear();

    Renderer2D::BeginScene( m_CameraController.GetCamera() );

    m_Scene->OnUpdate( ts );
    Renderer2D::EndScene();

    m_Framebuffer->Unbind();
  }

  void EditorLayer::OnImGuiRender()
  {
    BSD_PROFILE_FUNCTION();

    static bool opt_fullscreen                = true;
    static bool opt_padding                   = false;
    static bool open                          = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if ( opt_fullscreen )
    {
      const ImGuiViewport* viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos( viewport->WorkPos );
      ImGui::SetNextWindowSize( viewport->WorkSize );
      ImGui::SetNextWindowViewport( viewport->ID );
      ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
      ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
      window_flags |=
          ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
      window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
      dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if ( dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode )
      window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking,
    // otherwise any change of dockspace/settings would lead to windows being stuck in limbo and
    // never being visible.
    if ( !opt_padding )
      ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );
    ImGui::Begin( "DockSpace Demo", &open, window_flags );
    if ( !opt_padding )
      ImGui::PopStyleVar();

    if ( opt_fullscreen )
      ImGui::PopStyleVar( 2 );

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if ( io.ConfigFlags & ImGuiConfigFlags_DockingEnable )
    {
      ImGuiID dockspace_id = ImGui::GetID( "MyDockSpace" );
      ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), dockspace_flags );
    }

    if ( ImGui::BeginMenuBar() )
    {
      if ( ImGui::BeginMenu( "Window" ) )
      {
        if ( ImGui::MenuItem( "Exit" ) )
          Application::Get().Close();

        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
    ImGui::Begin( "Settings" );
    auto stats = Renderer2D::GetStats();
    ImGui::Text( "Renderer2D Stats:" );
    ImGui::Text( "Draw Calls: %d", stats.DrawCalls );
    ImGui::Text( "Quad Count: %d", stats.QuadCount );
    ImGui::Text( "Total Vertex Count: %d", stats.GetTotalVertexCount() );
    ImGui::Text( "Total Index Count: %d", stats.GetTotalIndexCount() );

    auto& squareColor = m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;
    ImGui::ColorEdit4( "Square Color", glm::value_ptr( squareColor ) );

    ImGui::End();

    ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0, 0 ) );

    ImGui::Begin( "Viewport" );
    m_IsViewportFocused = ImGui::IsWindowFocused();
    m_IsViewportHovered = ImGui::IsWindowHovered();

    Application::Get().GetImGuiLayer()->SetBlockEvents( !m_IsViewportFocused || !m_IsViewportHovered );
    BSD_CORE_WARN( "Focused: {0}", ImGui::IsWindowFocused() );
    BSD_CORE_WARN( "Hovered: {0}", ImGui::IsWindowHovered() );
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    if ( m_ViewportSize != *( (glm::vec2*)&viewportPanelSize ) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0 )
    {
      m_Framebuffer->Resize( viewportPanelSize.x, viewportPanelSize.y );
      m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
      m_CameraController.OnResize( viewportPanelSize.x, viewportPanelSize.y );
    }
    BSD_WARN( "Viewport Size: {0}, {1}", viewportPanelSize.x, viewportPanelSize.y );
    uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
    ImGui::Image( (void*)textureID, ImVec2( m_ViewportSize.x, m_ViewportSize.y ), ImVec2( 0, 1 ), ImVec2( 1, 0 ) );
    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::End();
  }

  void EditorLayer::OnEvent( Event& e ) { m_CameraController.OnEvent( e ); }
} // namespace Based
