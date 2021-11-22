#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace bmets::render {

  class Texture;

  struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
  };

  struct Material {
    Texture* texture;
    glm::vec4 diffuse_color;

    Material() { }
    Material(Texture* texture, glm::vec4 diffuse_color);
    void bind();
    int get_priority();
  };

  class Mesh {
  public:
    Material material;
    size_t indices_size;

    // Forbid copying: Copying will result in double-free of GL buffers
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, Material material);
    ~Mesh();

    unsigned int generate_vao();
    
    unsigned int vbo = 0, ebo = 0, non_instance_vao = 0;
  };

  class InstanceChunk {
  public:
    unsigned int vbo_fwd;
    unsigned int vbo_rev;
    std::vector<unsigned int> vaos_fwd;
    std::vector<unsigned int> vaos_rev;
    int id_begin;
    int size;

    InstanceChunk() {}
    ~InstanceChunk();
    // Forbid copying: Copying will result in double-free of GL buffers
    InstanceChunk(const InstanceChunk&) = delete;
    InstanceChunk& operator=(const InstanceChunk&) = delete;
    InstanceChunk(InstanceChunk&& src) {
      vbo_fwd = src.vbo_fwd; src.vbo_fwd = 0;
      vbo_rev = src.vbo_rev; src.vbo_rev = 0;
      vaos_fwd = std::move(src.vaos_fwd);
      vaos_rev = std::move(src.vaos_rev);
      size = src.size; id_begin = src.id_begin;
    }
  };

  class Model {
  public:
    std::vector<std::unique_ptr<Mesh>> meshes;
    std::string file_path;
    int priority;
    int opaque_meshes_count;
    
    Model(std::string& path);
    void load();
    void draw(glm::mat4 transform, int priority);
    void opacity_sort();
    void generate_vaos(std::vector<unsigned int> &out, unsigned int instance_vbo);
  };

  class ModelList {
  public:
    std::unique_ptr<Model> prefab;
    std::vector<glm::mat4> transforms;
    std::vector<double> locations;

    // Forbid copying: unique_ptr
    ModelList(const ModelList&) = delete;
    ModelList& operator=(const ModelList&) = delete;
    ModelList() { }
    ModelList(std::string& path);
    ~ModelList();

    void clear_instances();
    void add_instance(glm::mat4 transform, double location);
    void generate_vaos();
    void draw(double begin, int priority);
  private:
    std::unordered_map<int, InstanceChunk> chunks;
    mutable int lookup_ptr_begin = 0, lookup_ptr_end = 0;
  };

  class ModelManager {
  public:
    std::unordered_map<std::string, std::unique_ptr<ModelList>> model_lists;
    std::vector<ModelList*> alpha_lists;
    unsigned int uniform_location_diffuse_color;
    mutable int draw_call_count;

    int cull_distance = 1000;
    int cull_policy = 0;
    // Store all instances in one VBO. Renders everything.
    static const int CULL_NONE = 0;
    // Store all instances in one VBO. Renders with BaseInstance
    static const int CULL_GL4 = 1;
    // Each VBO contains instances within (2*cull_distance),
    //   1 draw calls (which draws twice as needed) for each mesh per frame
    //   Uses less draw calls but draws more faces
    static const int CULL_GL3_APPROX = 2;
    // Each VBO contains instances within (cull_distance),
    //   2 draw calls for each mesh per frame
    //   Uses more draw calls to draw less faces
    static const int CULL_GL3_ACCURATE = 3;

    // Unload models (instances & prefabs)
    void clear() {
      model_lists.clear();
      alpha_lists.clear();
    }

    // Clear instances, keep prefabs
    void clear_instances() {
      for (auto &list : model_lists) list.second->clear_instances();
    }

    // Step 1: Register the models to be used.
    void add_model(std::string key, std::string path);
    ModelList* get_model(std::string key);

    // Step 2: Load models from disk.
    void load_all(int loadFlag);

    // Step 3: Generate opacity info.
    void opacity_sort();

    // Step 4: Generate instance buffers.
    void generate_vaos(int cullPolicy);

    // Draw.
    void draw_all(double begin); 
  };

}