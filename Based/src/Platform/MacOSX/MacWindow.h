#pragma once
#include "Based/Window.h"
#include "Based/Renderer/RendererContext.h"

// --- Modern OpenGL Static Library
#include <glad/glad.h>

// --- GLFW Static Library
#include <GLFW/glfw3.h>


namespace Based {
class MacWindow : public Window {
public:
  MacWindow(const WindowProps &props);
  virtual ~MacWindow();

  void OnUpdate() override;

  inline unsigned int GetWidth() const override { return m_Data.Width; }
  inline unsigned int GetHeight() const override { return m_Data.Height; }

  // Window attributes
  inline void SetEventCallback(const EventCallbackFn &callback) override {
    m_Data.EventCallback = callback;
  }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

  inline virtual void *GetNativeWindow() const override { return m_Window; }

private:
  virtual void Init(const WindowProps &props);
  virtual void Shutdown();

private:
  GLFWwindow *m_Window;
  RendererContext* m_Context;
  struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;

    EventCallbackFn EventCallback;
  };

  WindowData m_Data;
};
} // namespace Based
