// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <string>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "core/renderer/mesh.h"
#include "core/renderer/shader.h"
#include "core/renderer/texture.h"

namespace prototype::renderer {

class Model {
 public:
  // constructor, expects a filepath to a 3D model.
  Model(const std::string& path);

  // draws the model, and thus all its meshes
  void Draw(Shader& shader);

 private:
  // loads a model with supported ASSIMP extensions from file and stores the
  // resulting meshes in the meshes vector.
  void LoadModel(const std::string& path);
  // processes a node in a recursive fashion. Processes each individual mesh
  // located at the node and repeats this process on its children nodes (if
  // any).
  void ProcessNode(aiNode* node, const aiScene* scene);
  Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
  // checks all material textures of a given type and loads the textures if
  // they're not loaded yet. the required info is returned as a Texture struct.
  std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                            const std::string& type_name);

  // model data
  std::vector<Texture>
      textures_loaded_;  // stores all the textures loaded so far, optimization
                         // to make sure textures aren't loaded more than once.
  std::vector<Mesh> meshes_;
  std::string directory_;
};

}  // namespace prototype::renderer
