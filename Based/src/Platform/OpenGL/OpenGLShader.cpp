#include "OpenGLShader.h"
#include "bsdpch.h"

#include <fstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Based {

static GLenum ShaderTypeFromString(const std::string &type) {
  if (type == "vertex")
    return GL_VERTEX_SHADER;
  if (type == "fragment" || type == "pixel ")
    return GL_FRAGMENT_SHADER;

  BSD_CORE_ASSERT(false, "Unknown shader type");
  return 0;
}

OpenGLShader::OpenGLShader(const std::string &filePath) {
  BSD_PROFILE_FUNCTION();
  std::string source = ReadFile(filePath);
  auto shaderSources = PreProcess(source);
  Compile(shaderSources);

  // Extract name from filePath
  auto lastSlash = filePath.find_last_of("/\\");
  lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
  auto lastDot = filePath.rfind(".");
  auto count = lastDot == std::string::npos ? filePath.size() - lastSlash
                                            : lastDot - lastSlash;
  m_ShaderName = filePath.substr(lastSlash, count);
}

OpenGLShader::OpenGLShader(const std::string &name,
                           const std::string &vertexSrc,
                           const std::string &fragmentSrc)
    : m_ShaderName(name) {
  BSD_PROFILE_FUNCTION();
  std::unordered_map<GLenum, std::string> sources;
  sources[GL_VERTEX_SHADER] = vertexSrc;
  sources[GL_FRAGMENT_SHADER] = fragmentSrc;
  Compile(sources);
}

void OpenGLShader::Compile(
    const std::unordered_map<GLenum, std::string> &shaderSources) {
  BSD_PROFILE_FUNCTION();

  GLuint program = glCreateProgram();
  BSD_CORE_ASSERT(shaderSources.size() <= 2,
                  "Currently only support two shaders");
  std::array<GLenum, 2> glShaderIDs;
  int glShaderIDIndex = 0;
  for (auto &kv : shaderSources) {
    GLenum type = kv.first;
    const std::string &source = kv.second;

    GLuint shader = glCreateShader(type);

    const GLchar *sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, 0);

    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

      glDeleteShader(shader);

      BSD_CORE_ERROR("{0}, within shader compiler", infoLog.data());
      BSD_CORE_ASSERT(false, "Shader compilation failure")
      break;
    }

    glAttachShader(program, shader);
    glShaderIDs[glShaderIDIndex++] = shader;
  }

  glLinkProgram(program);

  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    glDeleteProgram(program);
    for (auto id : glShaderIDs)
      glDeleteShader(id);

    BSD_CORE_ERROR("{0}, within shader linker", infoLog.data());
    BSD_CORE_ASSERT(false, "Shader link failure")
    return;
  }

  for (auto id : glShaderIDs) {
    glDetachShader(program, id);
    glDeleteShader(id);
  }
  m_ShaderID = program;
}

OpenGLShader::~OpenGLShader() {
  BSD_PROFILE_FUNCTION();
  glDeleteProgram(m_ShaderID);
}

std::string OpenGLShader::ReadFile(const std::string &filePath) {
  BSD_PROFILE_FUNCTION();
  std::string result;
  std::ifstream in(filePath, std::ios::in | std::ios::binary);

  if (in) {
    in.seekg(0, std::ios::end);
    result.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&result[0], result.size());
    in.close();
  } else {
    BSD_CORE_ERROR("Could not open file '{0}'", filePath);
  }

  return result;
}

std::unordered_map<GLenum, std::string>
OpenGLShader::PreProcess(const std::string &source) {
  std::unordered_map<GLenum, std::string> shaderSources;

  const char *typeToken = "#type";
  size_t typeTokenLength = strlen(typeToken);
  size_t pos = source.find(typeToken, 0);

  while (pos != std::string::npos) {
    size_t eol = source.find_first_of("\r\n", pos);
    BSD_CORE_ASSERT(eol != std::string::npos, "Syntax error");
    size_t begin = pos + typeTokenLength + 1;
    std::string type = source.substr(begin, eol - begin);
    BSD_CORE_ASSERT(ShaderTypeFromString(type),
                    "Invalid shader type specification");

    size_t nextLinePos = source.find_first_not_of("\r\n", eol);
    pos = source.find(typeToken, nextLinePos);
    shaderSources[ShaderTypeFromString(type)] = source.substr(
        nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1
                                                             : nextLinePos));
  }
  return shaderSources;
}

void OpenGLShader::Bind() const {
  BSD_PROFILE_FUNCTION();
  glUseProgram(m_ShaderID);
}

void OpenGLShader::Unbind() const {
  BSD_PROFILE_FUNCTION();
  glUseProgram(0);
}

void OpenGLShader::SetInt(const std::string &name, const int &value) {
  UploadUniformInt(name, value);
}
void OpenGLShader::SetFloat(const std::string &name, float value) {
  UploadUniformFloat(name, value);
}
void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &value) {
  UploadUniformFloat3(name, value);
}
void OpenGLShader::SetFloat4(const std::string &name, const glm::vec4 &value) {
  UploadUniformFloat4(name, value);
}
void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value) {
  UploadUniformMat4(name, value);
}

void OpenGLShader::UploadUniformInt(const std::string &name, int value) {
  GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
  glUniform1i(location, value);
}

void OpenGLShader::UploadUniformFloat(const std::string &name, float value) {
  GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
  glUniform1f(location, value);
}

void OpenGLShader::UploadUniformFloat2(const std::string &name,
                                       const glm::vec2 &value) {
  GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
  glUniform2f(location, value.x, value.y);
}

void OpenGLShader::UploadUniformFloat3(const std::string &name,
                                       const glm::vec3 &value) {
  GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
  glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::UploadUniformFloat4(const std::string &name,
                                       const glm::vec4 &value) {
  GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
  glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::UploadUniformMat3(const std::string &name,
                                     const glm::mat3 &matrix) {
  GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::UploadUniformMat4(const std::string &name,
                                     const glm::mat4 &matrix) {
  GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace Based
