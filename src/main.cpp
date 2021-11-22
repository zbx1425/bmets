#include <string>
#include <iostream>
#include "render/MainLoop.h"
#include "render/SceneMain.h"
#include "render/SceneImgui.h"

using namespace bmets::render;

int main() {
  g_CurrentScene = std::make_unique<SceneMain>();
  return run_main_loop();
}