#pragma once
#include "Based/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Based {
class OpenGLContext: public RendererContext {
public:
  OpenGLContext(GLFWwindow *windowHandle);

  virtual void Init() override;
  virtual void SwapBuffers() override;


private:
  GLFWwindow *m_WindowHandle;
  };
}
