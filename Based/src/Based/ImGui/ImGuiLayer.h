#pragma once

#include "Based/Core/Layer.h"

namespace Based
{
    class ImGuiLayer : public Layer
    {
        public:
            ImGuiLayer();
            ~ImGuiLayer() = default;

            virtual void OnAttach() override;
            virtual void OnDetach() override;
            virtual void OnEvent( Event& e ) override;

            void Begin();
            void End();

            void SetBlockEvents( bool block ) { m_BlockEvents = block; }

        private:
            bool m_BlockEvents = true;
            float m_Time       = 0.0f;
    };

} // namespace Based
