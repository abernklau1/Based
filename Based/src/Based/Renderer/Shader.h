#pragma once

#include "bsdpch.h"
#include "Based/Log.h"

namespace Based {
class Shader {
public:
  Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
  ~Shader();

  void Bind() const;
  void Unbind() const;

private:
  uint32_t m_RendererID;
};
}
