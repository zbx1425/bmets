#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include <queue>

namespace bmets::render {

  extern ModelManager model_manager;
  extern TextureManager texture_manager;

  void reset(int loadFlag);
  void acquire_uniform_locations(Shader* shader);
}