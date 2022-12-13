#include "Platform/MacOSX/MacWindow.h"
#include "bsdpch.h"

#include "Based/Core/Input.h"

// Events
#include "Based/Events/ApplicationEvent.h"
#include "Based/Events/KeyEvent.h"
#include "Based/Events/MouseEvent.h"

#include "Based/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Based {
static uint8_t s_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char *description) {
  BSD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

MacWindow::MacWindow(const WindowProps &props) {
  BSD_PROFILE_FUNCTION();
  Init(props);
}

MacWindow::~MacWindow() {
  BSD_PROFILE_FUNCTION();
  Shutdown();
}

void MacWindow::Init(const WindowProps &props) {
  BSD_PROFILE_FUNCTION();
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  BSD_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
                props.Height);

  if (s_GLFWWindowCount == 0) {
    int success = glfwInit();
    BSD_CORE_ASSERT(success, "Could not initialize GLFW!");
    glfwSetErrorCallback(GLFWErrorCallback);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only */
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  m_Window = glfwCreateWindow((int)props.Width, (int)props.Height,
                              m_Data.Title.c_str(), nullptr, nullptr);
  ++s_GLFWWindowCount;
  m_Context = RendererContext::Create(m_Window);
  m_Context->Init();

  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(
      m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
      });

  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.EventCallback(event);
  });

  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode,
                                  int action, int mods) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    switch (action) {
    case GLFW_PRESS: {
      KeyPressedEvent event(static_cast<KeyCode>(key), 0);
      data.EventCallback(event);
      break;
    }
    case GLFW_RELEASE: {
      KeyReleasedEvent event(static_cast<KeyCode>(key));
      data.EventCallback(event);
      break;
    }
    case GLFW_REPEAT: {
      KeyPressedEvent event(static_cast<KeyCode>(key), 1);
      data.EventCallback(event);
      break;
    }
    }
  });

  glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    KeyTypedEvent event(static_cast<KeyCode>(keycode));
    data.EventCallback(event);
  });

  glfwSetMouseButtonCallback(
      m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
          MouseButtonPressedEvent event(static_cast<MouseCode>(button));
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE: {
          MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
          data.EventCallback(event);
          break;
        }
        case GLFW_REPEAT: {
          MouseButtonPressedEvent event(static_cast<MouseCode>(button));
          data.EventCallback(event);
          break;
        }
        }
      });

  glfwSetScrollCallback(
      m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
      });

  glfwSetCursorPosCallback(
      m_Window, [](GLFWwindow *window, double xPos, double yPos) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
      });
}

void MacWindow::Shutdown() {
  BSD_PROFILE_FUNCTION();
  glfwDestroyWindow(m_Window);
  --s_GLFWWindowCount;

  if (s_GLFWWindowCount == 0)
    glfwTerminate();
}

void MacWindow::OnUpdate() {
  BSD_PROFILE_FUNCTION();
  glfwPollEvents();
  m_Context->SwapBuffers();
}

void MacWindow::SetVSync(bool enabled) {
  BSD_PROFILE_FUNCTION();
  if (enabled)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);

  m_Data.VSync = enabled;
}

bool MacWindow::IsVSync() const { return m_Data.VSync; }

} // namespace Based
