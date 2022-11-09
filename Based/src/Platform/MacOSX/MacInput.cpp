#include "MacInput.h"
#include "Based/Core/Application.h"
#include "bsdpch.h"

#include <GLFW/glfw3.h>

namespace Based {

Input *Input::s_Instance = new MacInput();

bool MacInput::IsKeyPressedImpl(int keycode) {
  auto window = static_cast<GLFWwindow *>(
      Application::Get().GetWindow().GetNativeWindow());

  auto state = glfwGetKey(window, keycode);
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool MacInput::IsMouseButtonPressedImpl(int button) {
  auto window = static_cast<GLFWwindow *>(
      Application::Get().GetWindow().GetNativeWindow());

  auto state = glfwGetMouseButton(window, button);
  return state == GLFW_PRESS;
}

float MacInput::GetMouseXImpl() {
  auto [x, y] = GetMousePosImpl();

  return x;
}

float MacInput::GetMouseYImpl() {
  auto [x, y] = GetMousePosImpl();
  return y;
}

std::pair<float, float> MacInput::GetMousePosImpl() {
  auto window = static_cast<GLFWwindow *>(
      Application::Get().GetWindow().GetNativeWindow());

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  return {(float)xpos, (float)ypos};
}
} // namespace Based
