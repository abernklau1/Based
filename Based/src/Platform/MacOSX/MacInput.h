#pragma once

#include "Based/Core/Input.h"

namespace Based {
class MacInput : public Input {
protected:
  virtual bool IsKeyPressedImpl(int keycode) override;

  virtual bool IsMouseButtonPressedImpl(int button) override;
  virtual float GetMouseXImpl() override;
  virtual float GetMouseYImpl() override;
  virtual std::pair<float, float> GetMousePosImpl() override;
};
} // namespace Based
