// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/model.h"

#include "assimp/postprocess.h"
#include "core/log.h"
#include "stb/stb_image.h"

namespace prototype::renderer {

// constructor, expects a filepath to a 3D model.
Model::Model(const std::filesystem::path& path) : model_path_(path) {
  LoadModel(path);
}

// draws the model, and thus all its meshes
void Model::Draw(Shader& shader) {
  for (unsigned int i = 0; i < meshes_.size(); i++) {
    meshes_[i].Draw(shader);
  }
}

// loads a model with supported ASSIMP extensions from file and stores the
// resulting meshes in the meshes vector.
void Model::LoadModel(const std::filesystem::path& path) {
  // read file via ASSIMP
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(
      path.string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                         aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  // check for errors
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode)  // if is Not Zero
  {
    CORE_LOG_ERROR("ERROR::ASSIMP:: {}", importer.GetErrorString());
    return;
  }

  // process ASSIMP's root node recursively
  ProcessNode(scene->mRootNode, scene);
}

// processes a node in a recursive fashion. Processes each individual mesh
// located at the node and repeats this process on its children nodes (if
// any).
void Model::ProcessNode(aiNode* node, const aiScene* scene) {
  // process each mesh located at the current node
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    // the node object only contains indices to index the actual objects in
    // the scene. the scene contains all the data, node is just to keep stuff
    // organized (like relations between nodes).
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes_.push_back(ProcessMesh(mesh, scene));
  }
  // after we've processed all of the meshes (if any) we then recursively
  // process each of the children nodes
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene);
  }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
  // data to fill
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  // walk through each of the mesh's vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    glm::vec3 vector;  // we declare a placeholder vector since assimp uses
                       // its own vector class that doesn't directly convert
                       // to glm's vec3 class so we transfer the data to this
                       // placeholder glm::vec3 first.
    // positions
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.position = vector;
    // normals
    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.normal = vector;
    }
    // texture coordinates
    if (mesh->mTextureCoords[0])  // does the mesh contain texture
                                  // coordinates?
    {
      glm::vec2 vec;
      // a vertex can contain up to 8 different texture coordinates. We thus
      // make the assumption that we won't use models where a vertex can have
      // multiple texture coordinates so we always take the first set (0).
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.tex_coords = vec;
      // tangent
      vector.x = mesh->mTangents[i].x;
      vector.y = mesh->mTangents[i].y;
      vector.z = mesh->mTangents[i].z;
      vertex.tangent = vector;
      // bitangent
      vector.x = mesh->mBitangents[i].x;
      vector.y = mesh->mBitangents[i].y;
      vector.z = mesh->mBitangents[i].z;
      vertex.bitangent = vector;
    } else {
      vertex.tex_coords = glm::vec2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }
  // now wak through each of the mesh's faces (a face is a mesh its triangle)
  // and retrieve the corresponding vertex indices.
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    // retrieve all indices of the face and store them in the indices vector
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }
  // process materials
  aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
  // we assume a convention for sampler names in the shaders. Each diffuse
  // texture should be named as 'texture_diffuseN' where N is a sequential
  // number ranging from 1 to MAX_SAMPLER_NUMBER. Same applies to other
  // texture as the following list summarizes: diffuse: texture_diffuseN
  // specular: texture_specularN
  // normal: texture_normalN

  // 1. diffuse maps
  auto diffuse_maps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
  // 2. specular maps
  auto specular_maps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
  // 3. normal maps
  auto normal_maps = LoadMaterialTextures(material, aiTextureType_NORMALS);
  // 4. height maps
  auto height_maps = LoadMaterialTextures(material, aiTextureType_HEIGHT);

  // return a mesh object created from the extracted mesh data
  return Mesh(vertices, indices, diffuse_maps);
}

// checks all material textures of a given type and loads the textures if
// they're not loaded yet. the required info is returned as a Texture struct.
std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat,
                                                 aiTextureType type) {
  std::vector<Texture> textures;
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);

    // check if texture was loaded before and if so, continue to next
    // iteration: skip loading a new texture
    auto loaded = std::find_if(textures_loaded_.begin(), textures_loaded_.end(),
                               [&str](const auto& loaded) {
                                 return loaded == str.C_Str();
                               }) != textures_loaded_.end();
    if (loaded) {
      continue;
    }

    Texture texture =
        LoadTexture(model_path_.replace_filename(str.C_Str()), true);
    textures.push_back(texture);
    textures_loaded_.push_back(
        str.C_Str());  // store it as texture loaded for entire model, to ensure
                       // we won't unnecessary load duplicate textures.
  }
  return textures;
}
}  // namespace prototype::renderer
