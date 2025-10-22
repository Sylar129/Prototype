// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <vector>

#include "core/renderer/shader.h"
#include "core/renderer/texture.h"
#include "glm/glm.hpp"

namespace prototype::renderer {

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
       const std::vector<unsigned int>& indices,
       const std::vector<Texture>& textures);
  void Draw(Shader& shader);

 private:
  void SetupMesh();
  std::vector<Vertex> vertices_;
  std::vector<unsigned int> indices_;
  std::vector<Texture> diiffuse_maps_;
  std::vector<Texture> specular_maps_;
  std::vector<Texture> normal_maps_;
  std::vector<Texture> height_maps_;
  unsigned int vao_, vbo_, ebo_;
};

}  // namespace prototype::renderer
