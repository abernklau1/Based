#include "bsdpch.h"
#include "Based/Log.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Based {

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle) {
BSD_CORE_ASSERT(windowHandle, "Window Handle is null");
}

void OpenGLContext::Init() {

  glfwMakeContextCurrent(m_WindowHandle);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  BSD_CORE_ASSERT(status, "Failed to initialize Glad");

  BSD_CORE_INFO("OpenGL Info:");
  BSD_CORE_INFO("  Vendor:   {0}", glGetString(GL_VENDOR));
  BSD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
  BSD_CORE_INFO("  Version:  {0}", glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers() {
  glfwSwapBuffers(m_WindowHandle);
}

}
