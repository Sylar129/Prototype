// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <vector>

#include "core/renderer/material.h"
#include "core/renderer/shader.h"
#include "core/renderer/texture.h"
#include "glm/glm.hpp"

namespace prototype {

#define MAX_BONE_INFLUENCE 4

struct Vertex {
  // position
  glm::vec3 position;
  // normal
  glm::vec3 normal;
  // texCoords
  glm::vec2 tex_coords;
  // tangent
  glm::vec3 tangent;
  // bitangent
  glm::vec3 bitangent;
  // bone indexes which will influence this vertex
  int bone_ids[MAX_BONE_INFLUENCE];
  // weights from each bone
  float weights[MAX_BONE_INFLUENCE];
};

class Mesh {
 public:
  Mesh(const std::vector<Vertex>& vertices,
       const std::vector<uint32_t>& indices);

  void SetDiffuseMaps(const std::vector<Texture>& diffuse);
  void SetSpeculareMaps(const std::vector<Texture>& specular);
  void SetMaterial(const Material& material);

  void Draw(Shader& shader);

 private:
  void SetupMesh();
  std::vector<Vertex> vertices_;
  std::vector<uint32_t> indices_;
  std::vector<Texture> diffuse_maps_;
  std::vector<Texture> specular_maps_;
  Material material_;
  uint32_t vao_;
  uint32_t vbo_;
  uint32_t ebo_;
};

}  // namespace prototype
