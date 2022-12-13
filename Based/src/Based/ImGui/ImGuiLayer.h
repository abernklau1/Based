#pragma once

#include "Based/Core/Layer.h"

namespace Based {
class ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;

  void Begin();
  void End();

private:
  float m_Time = 0.0f;
};

} // namespace Based
