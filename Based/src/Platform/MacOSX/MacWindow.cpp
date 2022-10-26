#include "MacWindow.h"
#include "Based/Log.h"
#include "bsdpch.h"

// Events
#include "Based/Events/ApplicationEvent.h"
#include "Based/Events/KeyEvent.h"
#include "Based/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <glad/glad.h>

namespace Based {
static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description) {
  BSD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window *Window::Create(const WindowProps &props) {
  return new MacWindow(props);
}

MacWindow::MacWindow(const WindowProps &props) { Init(props); }

MacWindow::~MacWindow() { Shutdown(); }

void MacWindow::Init(const WindowProps &props) {
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;


  BSD_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
                props.Height);


  if (!s_GLFWInitialized) {
    // TODO: glfwTerminate on system shutdown
    int success = glfwInit();
    BSD_CORE_ASSERT(success, "Could not initialize GLFW!");
    glfwSetErrorCallback(GLFWErrorCallback);
    s_GLFWInitialized = true;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only */
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  m_Window = glfwCreateWindow((int)props.Width, (int)props.Height,
                              m_Data.Title.c_str(), nullptr, nullptr);

  m_Context = new OpenGLContext(m_Window);
  m_Context->Init();
  // ^


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
      KeyPressedEvent event(key, 0);
      data.EventCallback(event);
      break;
    }
    case GLFW_RELEASE: {
      KeyReleasedEvent event(key);
      data.EventCallback(event);
      break;
    }
    case GLFW_REPEAT: {
      KeyPressedEvent event(key, 1);
      data.EventCallback(event);
      break;
    }
    }
  });

  glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    KeyTypedEvent event(keycode);
    data.EventCallback(event);
  });

  glfwSetMouseButtonCallback(
      m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
          MouseButtonPressedEvent event(button);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE: {
          MouseButtonReleasedEvent event(button);
          data.EventCallback(event);
          break;
        }
        case GLFW_REPEAT: {
          MouseButtonPressedEvent event(button);
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

void MacWindow::Shutdown() { glfwDestroyWindow(m_Window); }

void MacWindow::OnUpdate() {
  glfwPollEvents();
  m_Context->SwapBuffers();
}

void MacWindow::SetVSync(bool enabled) {
  if (enabled)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);

  m_Data.VSync = enabled;
}

bool MacWindow::IsVSync() const { return m_Data.VSync; }

} // namespace Based