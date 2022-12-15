#include "Platform/MacOSX/MacInput.h"
#include "Based/Core/Application.h"
#include "bsdpch.h"

#include <GLFW/glfw3.h>

namespace Based
{

    bool MacInput::IsKeyPressedImpl(KeyCode key)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool MacInput::IsMouseButtonPressedImpl(MouseCode button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    std::pair<float, float> MacInput::GetMousePosImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return {(float)xpos, (float)ypos};
    }

    float MacInput::GetMouseXImpl()
    {
        auto [x, y] = GetMousePosImpl();

        return x;
    }

    float MacInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePosImpl();
        return y;
    }
} // namespace Based
