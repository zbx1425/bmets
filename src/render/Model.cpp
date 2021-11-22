#include "Model.h"
#include <boost/format.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../util/Path.h"
#include "Manager.h"
#include "../game/Manager.h"
#include "../util/FmtException.h"

using namespace bmets::render;

Material::Material(Texture* texture, glm::vec4 diffuse_color) {
  this->texture = texture;
  this->diffuse_color = diffuse_color;
}

void Material::bind() {
  glUniform4f(model_manager.uniform_location_diffuse_color, diffuse_color.x, diffuse_color.y, diffuse_color.z, diffuse_color.w);
  if (texture != nullptr) {
    texture->bind();
  } else {
    texture_manager.white_texture->bind();
  }
}

int Material::get_priority() {
  return diffuse_color.w < 1.0f ||
      (texture != nullptr && texture->priority == Texture::PRIORITY_ALPHA);
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, Material material) {
  this->material = material;
  this->indices_size = indices.size();

  glBindVertexArray(0);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  non_instance_vao = generate_vao();
}

Mesh::~Mesh() {
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &non_instance_vao);
}

unsigned int Mesh::generate_vao() {
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glEnableVertexAttribArray(0);	
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(1);	
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
  glEnableVertexAttribArray(2);	
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

  return vao;
}

Model::Model(std::string& path) {
  file_path = path;
}

void Model::load() {
  if (file_path.empty()) return; // Dummy model
  if (meshes.size() > 0) meshes.clear(); // Reload

  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(file_path, 
    aiProcess_Triangulate | aiProcess_FlipUVs 
    | aiProcess_GenNormals | aiProcess_OptimizeMeshes);
  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    bmets::game::loader_warn("Cannot load model, Assimp error: " + std::string(importer.GetErrorString()), file_path, -1);
    return;
  }
  for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[i];
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
      Vertex vertex;
      vertex.Position.x = mesh->mVertices[i].x;
      vertex.Position.y = mesh->mVertices[i].y;
      vertex.Position.z = mesh->mVertices[i].z;
      vertex.Normal.x = mesh->mNormals[i].x;
      vertex.Normal.y = mesh->mNormals[i].y;
      vertex.Normal.z = mesh->mNormals[i].z;
      if(mesh->mTextureCoords[0]) {
        vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
        vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
      } else {
        vertex.TexCoords.x = vertex.TexCoords.y = 0.0f;
      }
      vertices.push_back(vertex);
    }
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];
      for(unsigned int j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
    }
    Material mesh_material;
    if(mesh->mMaterialIndex >= 0) {
      aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

      aiColor3D color(1.f, 1.f, 1.f);
      float opacity = 1.0f;
      material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
      material->Get(AI_MATKEY_OPACITY, opacity);
      mesh_material.diffuse_color = glm::vec4 { color.r, color.g, color.b, opacity };

      mesh_material.texture = nullptr;
      if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        aiString mat_name;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &mat_name);
        std::string mat_path;
        try {
          mat_path = path_to_abs(std::string(mat_name.C_Str()), file_path);
        } catch (std::exception &ex) {
          bmets::game::loader_warn(std::string("Cannot find texture '") + mat_name.C_Str() + "' : " + ex.what(), file_path, -1);
        }
        if (mat_path.size() > 0) {
          mesh_material.texture = texture_manager.add_texture(mat_path);
        }
      }
    }
    meshes.push_back(std::make_unique<Mesh>(vertices, indices, mesh_material));
  }
}

void Model::draw(glm::mat4 transform, int priority) {
  int mesh_begin = priority == Texture::PRIORITY_ALPHA ? opaque_meshes_count : 0;
  int mesh_end = priority == Texture::PRIORITY_ALPHA ? meshes.size() : opaque_meshes_count;
  ++model_manager.draw_call_count;
  for (int i = mesh_begin; i < mesh_end; ++i) {
    glBindVertexArray(meshes[i]->non_instance_vao);
    meshes[i]->material.bind();
    glVertexAttrib4fv(4, (const GLfloat *)(&transform));
    glVertexAttrib4fv(5, (const GLfloat *)(&transform) + 4);
    glVertexAttrib4fv(6, (const GLfloat *)(&transform) + 8);
    glVertexAttrib4fv(7, (const GLfloat *)(&transform) + 12);
    glDrawElements(GL_TRIANGLES, meshes[i]->indices_size, GL_UNSIGNED_INT, (void*)0);
  }
}

void Model::opacity_sort() {
  std::sort(meshes.begin(), meshes.end(), [](const std::unique_ptr<Mesh>& a, const std::unique_ptr<Mesh>& b) {
    return a->material.get_priority() < b->material.get_priority();  
  });
  opaque_meshes_count = 0;
  for (auto &mesh : meshes) if (mesh->material.get_priority() == 0) opaque_meshes_count++;
  priority = opaque_meshes_count < meshes.size() ? Texture::PRIORITY_ALPHA : Texture::PRIORITY_OPAQUE;
}

void Model::generate_vaos(std::vector<unsigned int> &out, unsigned int instance_vbo) {
  // Generate vaos, opaque meshes first, then alpha meshes
  out.clear();
  for (auto &mesh : meshes) out.push_back(mesh->generate_vao());
  for (auto vao : out) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(0));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);
  }
}

InstanceChunk::~InstanceChunk() {
  if (vbo_fwd > 0) glDeleteBuffers(1, &vbo_fwd);
  if (vbo_rev > 0) glDeleteBuffers(1, &vbo_rev);
  if (!vaos_fwd.empty())
    glDeleteVertexArrays(vaos_fwd.size(), &vaos_fwd[0]);
  if (!vaos_rev.empty())
    glDeleteVertexArrays(vaos_rev.size(), &vaos_rev[0]);
}

ModelList::ModelList(std::string& path) {
  prefab = std::make_unique<Model>(path);
}

ModelList::~ModelList() {
  clear_instances();
}

void ModelList::add_instance(glm::mat4 transform, double location) {
  transforms.push_back(transform);
  locations.push_back(location);
}

void ModelList::clear_instances() {
  chunks.clear();
  transforms.clear();
  locations.clear();
  lookup_ptr_begin = 0;
  lookup_ptr_end = 0;
}

static inline int chunkofdist(int dist) {
  return dist / model_manager.cull_distance;
}

static void iterative_qsort(ModelList* list) {
  int stack[list->transforms.size()];
  int top = -1;
  stack[++top] = 0;
  stack[++top] = list->transforms.size() - 1;
  while (top >= 0) {
    int h = stack[top--], l = stack[top--];
    int x = list->locations[h];
    int i = (l - 1);
    for (int j = l; j <= h - 1; j++) {
      if (list->locations[j] <= x) {
        i++;
        std::swap(list->locations[i], list->locations[j]);
        std::swap(list->transforms[i], list->transforms[j]);
      }
    }
    std::swap(list->locations[i + 1], list->locations[h]);
    std::swap(list->transforms[i + 1], list->transforms[h]);
    int p = i + 1;
    if (p - 1 > l) {
      stack[++top] = l;
      stack[++top] = p - 1;
    }
    if (p + 1 < h) {
      stack[++top] = p + 1;
      stack[++top] = h;
    }
  }
}

void ModelList::generate_vaos() {
  if (transforms.size() == 0) return;
  chunks.clear();

  glBindVertexArray(0);
  switch (model_manager.cull_policy) {
  case ModelManager::CULL_GL4:
    iterative_qsort(this);
    // Intentional switch pass-through
  case ModelManager::CULL_NONE: {
    InstanceChunk chunk;
    chunk.id_begin = 0;
    chunk.size = locations.size();
    glGenBuffers(1, &chunk.vbo_fwd);
    glBindBuffer(GL_ARRAY_BUFFER, chunk.vbo_fwd);
    glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(glm::mat4),
      &transforms[0], GL_STATIC_DRAW);
    prefab->generate_vaos(chunk.vaos_fwd, chunk.vbo_fwd);
    chunks.emplace(0, std::move(chunk));
    break;
  }
  case ModelManager::CULL_GL3_APPROX: {
    iterative_qsort(this);
    int idBegin = 0, id1x = 0, id2x = 0, idLookup = 0, chunkBegin;

    while (idLookup < locations.size()) {
      chunkBegin = chunkofdist(locations[idBegin]);
      idLookup = idBegin;
      while (idLookup < locations.size() && chunkofdist(locations[idLookup]) < chunkBegin + 1) idLookup++;
      id1x = idLookup;
      while (idLookup < locations.size() && chunkofdist(locations[idLookup]) < chunkBegin + 2) idLookup++;
      id2x = idLookup;

      InstanceChunk chunk;
      chunk.id_begin = idBegin;
      chunk.size = id2x - idBegin;
      glGenBuffers(1, &chunk.vbo_fwd);
      glBindBuffer(GL_ARRAY_BUFFER, chunk.vbo_fwd);
      glBufferData(GL_ARRAY_BUFFER, (id2x - idBegin) * sizeof(glm::mat4),
        &transforms[idBegin], GL_STATIC_DRAW);
      prefab->generate_vaos(chunk.vaos_fwd, chunk.vbo_fwd);
      chunks.emplace(chunkBegin, std::move(chunk));
      idBegin = id1x;
    }
    break;
  }
  case ModelManager::CULL_GL3_ACCURATE: {
    iterative_qsort(this);
    // TODO
    break;
  }
  }
}

void ModelList::draw(double begin, int priority) {
  if (transforms.size() == 0) return;
  if (locations.back() < begin) return;
  int mesh_begin = priority == Texture::PRIORITY_ALPHA ? prefab->opaque_meshes_count : 0;
  int mesh_end = priority == Texture::PRIORITY_ALPHA ? prefab->meshes.size() : prefab->opaque_meshes_count;

  switch (model_manager.cull_policy) {
  case ModelManager::CULL_NONE: {
    for (int i = mesh_begin; i < mesh_end; ++i) {
      ++model_manager.draw_call_count;
      glBindVertexArray(chunks[0].vaos_fwd[i]);
      prefab->meshes[i]->material.bind();
      glDrawElementsInstanced(GL_TRIANGLES, prefab->meshes[i]->indices_size, GL_UNSIGNED_INT, (void*)0, chunks[0].size);
    }
    break;
  }
  case ModelManager::CULL_GL4: {
    double end = begin + model_manager.cull_distance;
    if (locations.front() > end) return;
    while (lookup_ptr_begin > 0 && locations[lookup_ptr_begin] > begin) lookup_ptr_begin--;
    while (lookup_ptr_begin < locations.size() - 1 && locations[lookup_ptr_begin + 1] < begin) lookup_ptr_begin++;

    while (lookup_ptr_end > 1 && locations[lookup_ptr_end - 1] > end) lookup_ptr_end--;
    while (lookup_ptr_end < locations.size() && locations[lookup_ptr_end] < end) lookup_ptr_end++;

    for (int i = mesh_begin; i < mesh_end; ++i) {
      ++model_manager.draw_call_count;
      glBindVertexArray(chunks[0].vaos_fwd[i]);
      prefab->meshes[i]->material.bind();
      glDrawElementsInstancedBaseInstance(GL_TRIANGLES, prefab->meshes[i]->indices_size, GL_UNSIGNED_INT, (void*)0, 
        lookup_ptr_begin, lookup_ptr_end - lookup_ptr_begin + 1);
    }
    break;
  }
  case ModelManager::CULL_GL3_APPROX: {
    auto chunkIt = chunks.find(chunkofdist(begin));
    if (chunkIt != chunks.end()) {
      for (int i = mesh_begin; i < mesh_end; ++i) {
        ++model_manager.draw_call_count;
        glBindVertexArray(chunkIt->second.vaos_fwd[i]);
        prefab->meshes[i]->material.bind();
        glDrawElementsInstanced(GL_TRIANGLES, prefab->meshes[i]->indices_size, GL_UNSIGNED_INT, (void*)0, chunkIt->second.size);
      }
    }
    break;
  }
  case ModelManager::CULL_GL3_ACCURATE: {
    // TODO
    break;
  }
  }
}

void ModelManager::add_model(std::string key, std::string path) {
  boost::to_lower(key);
  if (get_model(key) != nullptr) {
    throw FmtException("Duplicate structure key: %s", key.c_str());
  } else {
    model_lists[key] = std::make_unique<ModelList>(path);
  }
}

ModelList* ModelManager::get_model(std::string key) {
  boost::to_lower(key);
  if (key.empty()) return nullptr;
  auto iter = model_lists.find(key);
  if (iter == model_lists.end()) return nullptr;
  return (*iter).second.get();
}

void ModelManager::load_all(int loadFlag) {
  if (loadFlag & bmets::game::LOAD_SKIP_STRUCTURE) return;
  
  int processing = 0;
  for (auto &list : model_lists) {
    if (processing % 50 == 0) {
      bmets::game::loader_progress((boost::format("Loading models ( %d / %d ) ...") 
        % processing % model_lists.size()).str(), -1);
    }
    list.second->prefab->load();
    processing++;
  }
}

void ModelManager::opacity_sort() {
  for (auto &list : model_lists) {
    list.second->prefab->opacity_sort();
  }
  alpha_lists.clear();
  for (auto &list : model_lists) {
    if (list.second->prefab->priority == Texture::PRIORITY_ALPHA) {
      alpha_lists.push_back(list.second.get());
    }
  }
}

void ModelManager::generate_vaos(int policy) {
  if (glDrawElementsInstancedBaseInstance == nullptr) {
    if (policy == CULL_GL4) policy = CULL_GL3_APPROX;
  }
  cull_policy = policy;

  int processing = 0;
  for (auto &list : model_lists) {
    if (processing % 50 == 0) {
      bmets::game::loader_progress((boost::format("Generating instance data ( %d / %d ) ...") 
        % processing % model_manager.model_lists.size()).str(), -1);
    }
    processing++;
    list.second->generate_vaos();
  }
}

static bool list_priority_cmp(const ModelList& a, const ModelList& b) {
  return a.prefab->priority < b.prefab->priority;
}

void ModelManager::draw_all(double begin) {
  draw_call_count = 0;
  glDisable(GL_BLEND);
  for (auto &list : model_lists) {
    list.second->draw(begin, Texture::PRIORITY_OPAQUE);
  }
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  for (auto &list : alpha_lists) {
    list->draw(begin, Texture::PRIORITY_ALPHA);
  }
}
