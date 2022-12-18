#pragma once

#include <Based.h>

#include "ParticleSystem/ParticleSystem.h"

class Sandbox2D : public Based::Layer
{
    public:
        Sandbox2D();
        virtual ~Sandbox2D() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate( Based::Timestep ts ) override;
        virtual void OnImGuiRender() override;
        void OnEvent( Based::Event& e ) override;

    private:
        Based::OrthographicCameraController m_CameraController;

        // Temp
        Based::Ref<Based::Texture2D> m_CheckerboardTexture;
        Based::Ref<Based::Texture2D> m_SpriteSheet;
        Based::Ref<Based::SubTexture2D> m_TextureDirt, m_TexturePumpkin;
        Based::Ref<Based::Framebuffer> m_Framebuffer;

        glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };

        ParticleProps m_Particle;
        ParticleSystem m_ParticleSystem;
};
