#pragma once

#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include <memory>

namespace bmets::render {

  class SceneMain : public Scene {
  public:
    SceneMain();
    void setup(GLFWwindow* window) override;
    void hide(GLFWwindow* window) override;
    void loop(GLFWwindow* window, double elapsedTime) override;
    void update_viewport(int width, int height) override;
    ~SceneMain();
  private:
    std::unique_ptr<Shader> mainShader;
    unsigned int boxVao, boxVbo;
    int ulModelMat, ulViewMat, ulProjMat;
  };

}