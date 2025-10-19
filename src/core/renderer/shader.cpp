// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/shader.h"

#include <fstream>
#include <iostream>

#include "core/log.h"
#include "glad/gl.h"
#include "glm/gtc/type_ptr.hpp"

namespace prototype::renderer {

namespace {
std::string ReadTextFile(const std::filesystem::path& path) {
  std::ifstream file(path);

  if (!file.is_open()) {
    CORE_LOG_ERROR("Failed to open file: {}", path.string());
    return {};
  }

  std::ostringstream content_stream;
  content_stream << file.rdbuf();
  return content_stream.str();
}
}  // namespace

Shader::Shader() : id_(0) {}

void Shader::Compile(const std::filesystem::path& vertex_path,
                     const std::filesystem::path& fragment_path) {
  int success = 0;
  char info[512];

  std::string vertex_shader_src = ReadTextFile(vertex_path);
  std::string fragment_shader_src = ReadTextFile(fragment_path);

  // vertex shader
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar* source = (const GLchar*)vertex_shader_src.c_str();

  glShaderSource(vertex_shader, 1, &source, nullptr);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, nullptr, info);
    CORE_LOG_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED: {}", info);
  }

  // fragment shader
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  source = (const GLchar*)fragment_shader_src.c_str();
  glShaderSource(fragment_shader, 1, &source, nullptr);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, nullptr, info);
    CORE_LOG_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: {}", info);
  }

  // link shader
  id_ = glCreateProgram();
  glAttachShader(id_, vertex_shader);
  glAttachShader(id_, fragment_shader);

  glLinkProgram(id_);
  // check for linking errors
  glGetProgramiv(id_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id_, 512, nullptr, info);
    CORE_LOG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED: {}", info);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void Shader::Delete() {
  if (id_ != 0) {
    glDeleteProgram(id_);
    id_ = 0;
  }
}

Shader& Shader::Use() {
  glUseProgram(id_);
  return *this;
}

void Shader::SetBool(const std::string& name, bool value) {
  glUniform1i(glGetUniformLocation(id_, name.c_str()), (GLint)value);
}

void Shader::SetInt(const std::string& name, GLint value) {
  glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, GLfloat value) {
  glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& v) {
  glUniform2f(glGetUniformLocation(id_, name.c_str()), v.x, v.y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& v) {
  glUniform3f(glGetUniformLocation(id_, name.c_str()), v.x, v.y, v.z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& v) {
  glUniform4f(glGetUniformLocation(id_, name.c_str()), v.x, v.y, v.z, v.w);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& m) {
  glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(m));
}

}  // namespace prototype::renderer
