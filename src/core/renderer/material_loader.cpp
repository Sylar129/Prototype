// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/material_loader.h"

#include <iostream>
#include <sstream>

#include "core/renderer/image.h"
#include "glad/gl.h"

namespace prototype {

glm::vec3 MaterialLoader::GetColor3(const aiMaterial* mat, const char* key,
                                    unsigned int type, unsigned int idx,
                                    glm::vec3 fallback) {
  aiColor3D c;
  if (mat->Get(key, type, idx, c) == AI_SUCCESS)
    return glm::vec3(c.r, c.g, c.b);
  return fallback;
}

void MaterialLoader::LoadTextureType(const aiMaterial* mat, aiTextureType type,
                                     const std::string& typeName,
                                     const std::string& directory,
                                     MaterialData& outMat) {
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);

    std::string path = directory + "/" + str.C_Str();

    TextureInfo tex;
    tex.texture.GenerateFromImage(Image(path));
    tex.type = typeName;
    tex.path = str.C_Str();
    outMat.textures.push_back(tex);

    if (type == aiTextureType_DIFFUSE) outMat.hasDiffuseTex = true;
    if (type == aiTextureType_SPECULAR) outMat.hasSpecularTex = true;
    if (type == aiTextureType_NORMALS) outMat.hasNormalTex = true;
  }
}

MaterialData MaterialLoader::Load(const aiMaterial* mat,
                                  const std::string& directory) {
  MaterialData outMat;

  // --- Read color properties ---
  outMat.Ka = GetColor3(mat, AI_MATKEY_COLOR_AMBIENT, glm::vec3(1.0f));
  outMat.Kd = GetColor3(mat, AI_MATKEY_COLOR_DIFFUSE, glm::vec3(1.0f));
  outMat.Ks = GetColor3(mat, AI_MATKEY_COLOR_SPECULAR, glm::vec3(1.0f));
  outMat.Ke = GetColor3(mat, AI_MATKEY_COLOR_EMISSIVE, glm::vec3(0.0f));

  // --- Read scalar properties ---
  mat->Get(AI_MATKEY_SHININESS, outMat.Ns);
  mat->Get(AI_MATKEY_OPACITY, outMat.d);
  mat->Get(AI_MATKEY_REFRACTI, outMat.Ni);
  mat->Get(AI_MATKEY_SHADING_MODEL, outMat.illum);

  if (outMat.Ns <= 0.0f) outMat.Ns = 32.0f;

  // --- Load textures ---
  LoadTextureType(mat, aiTextureType_DIFFUSE, "diffuse", directory, outMat);
  LoadTextureType(mat, aiTextureType_SPECULAR, "specular", directory, outMat);
  LoadTextureType(mat, aiTextureType_NORMALS, "normal", directory, outMat);

  return outMat;
}

}  // namespace prototype
