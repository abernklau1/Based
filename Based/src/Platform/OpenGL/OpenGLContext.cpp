#include "OpenGLContext.h"
#include "Based/Core/Log.h"
#include "bsdpch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Based {

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle) {
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

#ifdef BSD_ENABLE_ASSERTS
  int versionMajor;
  int versionMinor;
  glGetInteger(GL_MAJOR_VERSION, &versionMajor);
  glGetInteger(GL_MINOR_VERSION, &versionMinor);

  BSD_CORE_ASSERT(versionMajor > 2 || (versionMajor == 4 && versionMinor >= 1),
                  "The Based Engine requires a minimum OpenGL version of 2.1");
#endif
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

} // namespace Based
