#pragma once

#include "Based/Core/Input.h"

namespace Based
{
    class MacInput : public Input
    {
        protected:
            virtual bool IsKeyPressedImpl(KeyCode key) override;

            virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
            virtual std::pair<float, float> GetMousePosImpl() override;
            virtual float GetMouseXImpl() override;
            virtual float GetMouseYImpl() override;
    };
} // namespace Based
