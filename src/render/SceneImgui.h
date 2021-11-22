#pragma once

#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include <memory>

class SceneImgui : public Scene {
public:
  SceneImgui();
  void setup(GLFWwindow* window) override;
  void hide(GLFWwindow* window) override;
  void loop(GLFWwindow* window, double elapsedTime) override;
  void update_viewport(int width, int height) override;
  ~SceneImgui();
};