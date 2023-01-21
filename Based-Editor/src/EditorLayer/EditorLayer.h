#pragma once

#include <Based.h>

namespace Based
{

  class EditorLayer : public Layer
  {
    public:
      EditorLayer();
      virtual ~EditorLayer() = default;

      virtual void OnAttach() override;
      virtual void OnDetach() override;

      void OnUpdate( Timestep ts ) override;
      virtual void OnImGuiRender() override;
      void OnEvent( Event& e ) override;

    private:
      OrthographicCameraController m_CameraController;

      // Temp
      Ref<Texture2D> m_CheckerboardTexture;
      Ref<Framebuffer> m_Framebuffer;
      Ref<Scene> m_Scene;

      Entity m_SquareEntity;

      bool m_IsViewportFocused = false;
      bool m_IsViewportHovered = false;
      glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
  };
} // namespace Based
