#pragma once
#include "Based/Core/Base.h"
#include "Based/Core/KeyCodes.h"
#include "Based/Core/MouseCodes.h"
#include "bsdpch.h"

namespace Based
{
    class Input
    {
        public:
            static bool IsKeyPressed( KeyCode key );

            static bool IsMouseButtonPressed( MouseCode button );

            static std::pair<float, float> GetMousePos();

            static float GetMouseX();

            static float GetMouseY();
    };

} // namespace Based
