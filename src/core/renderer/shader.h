// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <filesystem>

#include "glad/gl.h"
#include "glm/glm.hpp"

namespace prototype::renderer {

class Shader {
 public:
  Shader();

  void Compile(const std::filesystem::path& vertex_path,
               const std::filesystem::path& fragment_path);
  void Delete();

  Shader& Use();

  void SetBool(const std::string& name, bool value);
  void SetInt(const std::string& name, GLint value);
  void SetFloat(const std::string& name, GLfloat value);
  void SetVec2(const std::string& name, const glm::vec2& v);
  void SetVec3(const std::string& name, const glm::vec3& v);
  void SetVec4(const std::string& name, const glm::vec4& v);
  void SetMat4(const std::string& name, const glm::mat4& m);

 private:
  GLuint id_;
};

}  // namespace prototype::renderer
