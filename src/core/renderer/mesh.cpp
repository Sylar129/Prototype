// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/mesh.h"

namespace prototype::renderer {

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<unsigned int>& indices,
           const std::vector<Texture>& textures)
    : vertices_(vertices), indices_(indices), diiffuse_maps_(textures) {
  SetupMesh();
}

void Mesh::Draw(Shader& shader) {
  int texture_num = 0;

  unsigned int diffuse_num = 1;
  for (const auto& texture : diiffuse_maps_) {
    glActiveTexture(GL_TEXTURE0 + texture_num);

    shader.SetInt(
        ("material.texture_diffuse" + std::to_string(diffuse_num++)).c_str(),
        texture_num);
    glBindTexture(GL_TEXTURE_2D, texture.handle);
    texture_num++;
  }

  unsigned int specular_num = 1;
  for (const auto& texture : specular_maps_) {
    glActiveTexture(GL_TEXTURE0 + texture_num);

    shader.SetInt(
        ("material.texture_specular" + std::to_string(specular_num++)).c_str(),
        texture_num);
    glBindTexture(GL_TEXTURE_2D, texture.handle);
    texture_num++;
  }

  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(vao_);
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()),
                 GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Mesh::SetupMesh() {
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex),
               &vertices_[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int),
               &indices_[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, normal));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, tex_coords));

  glBindVertexArray(0);
}
}  // namespace prototype::renderer
