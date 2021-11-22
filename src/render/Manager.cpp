#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "../game/Manager.h"

namespace bmets::render {

  ModelManager model_manager;
  TextureManager texture_manager;

  void reset(int loadFlag) {
    if (loadFlag & bmets::game::LOAD_SKIP_STRUCTURE) {
      model_manager.clear_instances();
    } else {
      model_manager.clear();
      texture_manager.clear();
    }
  }

  void acquire_uniform_locations(Shader* shader) {
    model_manager.uniform_location_diffuse_color = shader->getUniformLocation("color_diffuse");
  }

}