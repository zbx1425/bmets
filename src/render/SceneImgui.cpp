#include "SceneImgui.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <iostream>
#include "../parser/BveMapScript.h"
#include "../math/Spline.h"
#include "../math/SPMainV.h"
#include "../math/SPMainL.h"
#include "../game/Map.h"

SceneImgui::SceneImgui() { }
SceneImgui::~SceneImgui() { }
void SceneImgui::hide(GLFWwindow* window) { }

bmets::game::Map map;
void SceneImgui::setup(GLFWwindow* window) { 
  bmets::parser::BveMapScript mapScript;
  //mapScript.load("F:/SharedUserWorkData/Documents/BveTs/Scenarios/shuttle/hrd/route/0756/map_0756a.txt");
  mapScript.load("F:/SharedUserWorkData/Documents/BveTs/Scenarios/mackoy.Keisei/Map.txt");
  //mapScript.load("test.txt");
  map.clear();
  map.parse_script_data(mapScript, 0);
};

float dx = -20.0f, dy = 100.0f, scale = 1.0f;
float vdx = -20.0f, vdy = 100.0f, vsx = 30.0f, vsy = 50.0f;

void SceneImgui::loop(GLFWwindow* window, double elapsedTime) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  if (ImGui::Button("Reload")) {
    hide(window);
    setup(window);
  }

{
  ImGui::Begin("L Spline");
  ImGui::SliderFloat2("x,y", &dx, -20.0f, 2000.0f);
  ImGui::SliderFloat("scale", &scale, 0.0f, 10.0f);
  auto idl = ImGui::GetWindowDrawList();
  auto pos = ImGui::GetWindowPos();

  auto last = map.track_main.l_spline.parts.back();
  for (int i = 0; i < last.begin + 10; i++) {
    map.track_main.l_spline.value_at(i);
      int color = (map.track_main.l_spline.lookup_ptr % 2 == 0) ? 85*2 : 85;
    idl->AddLine(
      ImVec2 { 
        static_cast<float>(map.track_main.l_spline.value_at(i).x - dx) * scale + pos.x, 
        static_cast<float>(map.track_main.l_spline.value_at(i).y + dy) * scale + pos.y
      },
      ImVec2 { 
        static_cast<float>(map.track_main.l_spline.value_at(i+1).x - dx) * scale + pos.x, 
        static_cast<float>(map.track_main.l_spline.value_at(i+1).y + dy) * scale + pos.y
      },
      ImColor(255, color, 255 - color, 255), 2.0F
    );
    if (i % 500 == 0) {
      idl->AddText(
        ImVec2 { 
          static_cast<float>(map.track_main.l_spline.value_at(i).x - dx) * scale + pos.x, 
          static_cast<float>(map.track_main.l_spline.value_at(i).y + dy) * scale + pos.y
        },
        ImColor(0, 255, 0, 255), std::to_string(i).c_str()
      );
    }
  }
  ImGui::End();
}

{
  ImGui::Begin("V Spline");
  ImGui::SliderFloat2("x,y", &vdx, -20.0f, 2000.0f);
  ImGui::SliderFloat2("scale x,y", &vsx, 0.0f, 50.0f);
  auto idl = ImGui::GetWindowDrawList();
  auto pos = ImGui::GetWindowPos();

  auto last = map.track_main.v_spline.parts.back();
  for (int i = 0; i < last.begin + 10; i++) {
    map.track_main.v_spline.value_at(i);
      int color = (map.track_main.v_spline.lookup_ptr % 2 == 0) ? 85*2 : 85;
    idl->AddLine(
      ImVec2 { 
        static_cast<float>(i - vdx) * (vsx / 100) + pos.x, 
        static_cast<float>(map.track_main.v_spline.value_at(i)) * vsy + vdy + pos.y
      },
      ImVec2 { 
        static_cast<float>(i+1 - vdx) * (vsx / 100) + pos.x, 
        static_cast<float>(map.track_main.v_spline.value_at(i+1)) * vsy + vdy + pos.y
      },
      ImColor(255, color, 255 - color, 255), 2.0F
    );
    if (i % 500 == 0) {
      idl->AddText(
        ImVec2 { 
          static_cast<float>(i - vdx) * (vsx / 100) + pos.x, 
          static_cast<float>(map.track_main.v_spline.value_at(i)) * vsy + vdy + pos.y
        },
        ImColor(0, 255, 0, 255), std::to_string(i).c_str()
      );
    }
  }
  ImGui::End();
}

  ImGui::Render();
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};

void SceneImgui::update_viewport(int width, int height) {
  glViewport(0, 0, width, height);
}