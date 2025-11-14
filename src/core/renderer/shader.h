// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <filesystem>
#include <memory>
#include <unordered_map>

#include "glad/gl.h"
#include "glm/glm.hpp"

namespace prototype {

class Camera;
struct PointLight;

class Shader {
 public:
  Shader();

  Shader& Use();

  void SetBool(const std::string& name, bool value);
  void SetInt(const std::string& name, GLint value);
  void SetFloat(const std::string& name, GLfloat value);
  void SetVec2(const std::string& name, const glm::vec2& v);
  void SetVec3(const std::string& name, const glm::vec3& v);
  void SetVec4(const std::string& name, const glm::vec4& v);
  void SetMat4(const std::string& name, const glm::mat4& m);

  void SetCamara(const std::string& name, const Camera& camera);
  void SetPointLight(const std::string& name, const PointLight& light);

 private:
  friend class ShaderLibrary;
  void Compile(const std::filesystem::path& vertex_path,
               const std::filesystem::path& fragment_path);
  void Delete();
  GLuint id_;
};

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

class ShaderLibrary {
 public:
  static ShaderLibrary& GetInstance();

  void Clean();

  void Add(const std::string& name, const Ref<Shader>& shader);
  Ref<Shader> Load(const std::string& name, const std::string& vert_path,
                   const std::string& frag_path);
  void Remove(const std::string& name);

  Ref<Shader> Get(const std::string& name);

  bool Exists(const std::string& name) const;

 private:
  ShaderLibrary() = default;
  std::unordered_map<std::string, Ref<Shader>> shaders_;
};

}  // namespace prototype
