// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <assimp/material.h>
#include <assimp/scene.h>

#include "Material.h"

namespace prototype {

struct TextureInfo {
  Texture texture;
  std::string path;
  std::string type;  // diffuse, specular, normal ...
};

struct MaterialData {
  // Colors
  glm::vec3 Ka = glm::vec3(1.0f);  // ambient
  glm::vec3 Kd = glm::vec3(1.0f);  // diffuse
  glm::vec3 Ks = glm::vec3(1.0f);  // specular
  glm::vec3 Ke = glm::vec3(0.0f);  // emissive

  // Params
  float Ns = 32.0f;  // shininess
  float Ni = 1.0f;   // IoR
  float d = 1.0f;    // alpha
  int illum = 2;     // illumination model

  // Textures
  bool hasDiffuseTex = false;
  bool hasSpecularTex = false;
  bool hasNormalTex = false;

  std::vector<TextureInfo> textures;  // loaded textures
};

class MaterialLoader {
 public:
  static MaterialData Load(const aiMaterial* mat, const std::string& directory);

 private:
  static glm::vec3 GetColor3(const aiMaterial* mat, const char* key,
                             unsigned int type, unsigned int idx,
                             glm::vec3 fallback);

  static void LoadTextureType(const aiMaterial* mat, aiTextureType type,
                              const std::string& typeName,
                              const std::string& directory,
                              MaterialData& outMat);
};
}  // namespace prototype
