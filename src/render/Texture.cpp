#include "Texture.h"
using namespace bmets::render;

#ifdef _WIN32
#define STBI_WINDOWS_UTF8
#endif
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../game/Manager.h"
#include "Manager.h"

#include <boost/format.hpp>
#include <boost/algorithm/string/case_conv.hpp>

std::unique_ptr<Texture> Texture::create_white_texture() {
  std::unique_ptr<Texture> white_texture = std::make_unique<Texture>();
  glGenTextures(1, &white_texture->id);
  glBindTexture(GL_TEXTURE_2D, white_texture->id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned char pixel_data[] = { 0xff, 0xff, 0xff, 0xff };
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data);
  white_texture->valid = true;
  return std::move(white_texture);
}

void Texture::load() {
  if (valid) return;
  if (path.empty()) return;

  unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

  if (data == nullptr) {
    bmets::game::loader_warn(std::string("Image loading failure: ") + stbi_failure_reason(), path, -1);
    valid = false;
  } else {
    int alphaPixelNum = 0;
    int thresholdPixelNum = width * height / 50;
    for (int p = 0; p < width * height - 1; ++p) {
      unsigned char pixel = data[p * 4 + 3];
      if (pixel > static_cast<unsigned char>(16) && pixel < static_cast<unsigned char>(240)) {
        ++alphaPixelNum;
        // if (alphaPixelNum > thresholdPixelNum) break;
      }
    }
    priority = (alphaPixelNum > thresholdPixelNum) ? PRIORITY_ALPHA : PRIORITY_OPAQUE;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    valid = true;
  }
}

Texture::~Texture() {
  #pragma warning (disable:4312)
  if (valid) glDeleteTextures(1, &id);
}

void Texture::bind() {
  if (valid) {
    glBindTexture(GL_TEXTURE_2D, id);
  } else {
    texture_manager.white_texture->bind();
  }
}

Texture* TextureManager::add_texture(std::string &path) {
  std::string path_small = boost::algorithm::to_lower_copy(path);
  auto iter = textures.find(path_small);
  if (iter == textures.end()) {
    auto ptr = std::make_unique<Texture>(path);
    auto rawPtr = ptr.get();
    textures.emplace(path_small, std::move(ptr));
    return rawPtr;
  } else {
    return (*iter).second.get();
  }
}

void TextureManager::load_all(int loadFlag) {
  if (loadFlag & bmets::game::LOAD_SKIP_STRUCTURE) return;
  
  int processing = 0;
  for (auto &pair : textures) {
    if (processing % 50 == 0) {
      bmets::game::loader_progress((boost::format("Loading textures ( %d / %d ) ...") 
        % processing % textures.size()).str(), -1);
    }
    pair.second->load();
    processing++;
  }
}