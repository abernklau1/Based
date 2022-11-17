#pragma once

#include "Based/Core/Core.h"
#include "Based/Core/Timestep.h"
#include "Based/Events/Event.h"

namespace Based {
class BASED_API Layer {
public:
  Layer(const std::string &name = "Layer");
  virtual ~Layer();

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate(Timestep ts) {}
  virtual void OnImGuiRender() {}
  virtual void OnEvent(Event &event) {}

  inline const std::string &GetName() const { return m_DebugName; }

protected:
  std::string m_DebugName;
};
} // namespace Based