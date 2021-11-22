#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace bmets::render {

  class Texture {
  public:
    int width, height, nrChannels;
    std::string path;
    bool valid = false;
    int priority;

    static const int PRIORITY_OPAQUE = 0;
    static const int PRIORITY_ALPHA = 1;

    Texture() { }
    Texture(std::string path) : path(path) { };
    // Forbid copying: Copying will result in double-free of GL textures
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    void load();
    void bind();
    static std::unique_ptr<Texture> create_white_texture();
    ~Texture();

  private:
    void load_dds(const char* path);
    void load_stb(const char* path);
    unsigned int id;
  };

  class TextureManager {
  public:
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
    std::unique_ptr<Texture> white_texture;

    void clear() {
      textures.clear();
      white_texture = Texture::create_white_texture();
    }

    // Step 1: Register a texture file.
    Texture* add_texture(std::string &path);

    // Step 2: Load textures from disk.
    void load_all(int loadFlag);

  };
  
}