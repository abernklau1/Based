#pragma once

#include <string>

namespace Based {
class Shader {
public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  // virtual void UploadUniformBuffer();

  static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

};
}
