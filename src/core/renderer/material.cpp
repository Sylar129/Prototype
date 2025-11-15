// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/material.h"

#include "assimp/material.h"
#include "core/log.h"
#include "core/renderer/shader.h"

namespace prototype {

Material Material::FromAssimp(const aiMaterial* material) {
  Material m;

  float shininess = 32.0f;  // default
  material->Get(AI_MATKEY_SHININESS, m.shininess);

  aiColor3D ka(1.0f, 1.0f, 1.0f);
  material->Get(AI_MATKEY_COLOR_AMBIENT, ka);
  m.specular = glm::vec3(ka.r, ka.g, ka.b);

  aiColor3D kd(1.0f, 1.0f, 1.0f);
  material->Get(AI_MATKEY_COLOR_DIFFUSE, kd);
  m.diffuse = glm::vec3(kd.r, kd.g, kd.b);

  aiColor3D ks(1.0f, 1.0f, 1.0f);
  material->Get(AI_MATKEY_COLOR_SPECULAR, ks);
  m.specular = glm::vec3(ks.r, ks.g, ks.b);

  return m;
}

void Material::UpdateShader() {
  auto& shader = *ShaderLibrary::GetInstance().Get("phong");
  CORE_LOG_ERROR(
      "UpdateShader ambient: {}, {}, {}, diffuse: {}, {}, {}, specular: {}, "
      "{}, {}, shininess: {}",
      ambient.x, ambient.y, ambient.z, diffuse.x, diffuse.y, diffuse.z,
      specular.x, specular.y, specular.z, shininess);
  shader.SetVec3("material.ambient", ambient);
  shader.SetVec3("material.diffuse", diffuse);
  shader.SetVec3("material.specular", specular);
  shader.SetFloat("material.shininess", shininess);
}

}  // namespace prototype
