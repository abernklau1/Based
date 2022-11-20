#pragma once

#include "Based/Core/Log.h"
#include "Based/Renderer/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Based {
class OpenGLShader : public Shader {
public:
  OpenGLShader(const std::string &filePath);
  OpenGLShader(const std::string &name, const std::string &vertexSrc,
               const std::string &fragmentSrc);
  virtual ~OpenGLShader();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual void SetInt(const std::string &name, const int &value) override;

  virtual void SetFloat(const std::string &name, float value) override;

  virtual void SetFloat3(const std::string &name,
                         const glm::vec3 &value) override;
  virtual void SetFloat4(const std::string &name,
                         const glm::vec4 &value) override;
  virtual void SetMat4(const std::string &name,
                       const glm::mat4 &value) override;

  virtual const std::string &GetName() const override { return m_ShaderName; }

  void UploadUniformInt(const std::string &name, int value);

  void UploadUniformFloat(const std::string &name, float value);
  void UploadUniformFloat2(const std::string &name, const glm::vec2 &value);
  void UploadUniformFloat3(const std::string &name, const glm::vec3 &value);
  void UploadUniformFloat4(const std::string &name, const glm::vec4 &value);

  void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
  void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

private:
  std::string ReadFile(const std::string &filePath);
  std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);
  void Compile(const std::unordered_map<GLenum, std::string> &shaderSources);

private:
  uint32_t m_ShaderID;

  std::string m_ShaderName;
};
} // namespace Based
