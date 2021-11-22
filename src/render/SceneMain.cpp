#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "SceneMain.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"
#include "Manager.h"
#include "../game/Map.h"
#include "../game/Manager.h"
#include "../parser/BveMapScript.h"

#include "../util/OpenFileDialog.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "ImFileBrowser.h"

#include <chrono>
#include <iostream>

using namespace bmets::render;
using namespace bmets::game;

SceneMain::SceneMain() {

}

SceneMain::~SceneMain() {

}

#define LINE_WIDTH 0.05
#define LINE_LEN 100000
glm::vec3 axis_vertices[] = {
  glm::vec3 { 0, LINE_WIDTH, 0 },
  glm::vec3 { LINE_LEN, LINE_WIDTH, 0 },
  glm::vec3 { LINE_LEN, -LINE_WIDTH, 0 },
  glm::vec3 { 0, -LINE_WIDTH, 0 },
  glm::vec3 { 0, 0, LINE_WIDTH },
  glm::vec3 { 0, LINE_LEN, LINE_WIDTH },
  glm::vec3 { 0, LINE_LEN, -LINE_WIDTH },
  glm::vec3 { 0, 0, -LINE_WIDTH },
  glm::vec3 { 0, LINE_WIDTH, 0 },
  glm::vec3 { 0, LINE_WIDTH, LINE_LEN },
  glm::vec3 { 0, -LINE_WIDTH, LINE_LEN },
  glm::vec3 { 0, -LINE_WIDTH, 0 },

  glm::vec3 { 0, LINE_WIDTH, 0 },
  glm::vec3 { -LINE_LEN, LINE_WIDTH, 0 },
  glm::vec3 { -LINE_LEN, -LINE_WIDTH, 0 },
  glm::vec3 { 0, -LINE_WIDTH, 0 },
  glm::vec3 { 0, 0, LINE_WIDTH },
  glm::vec3 { 0, -LINE_LEN, LINE_WIDTH },
  glm::vec3 { 0, -LINE_LEN, -LINE_WIDTH },
  glm::vec3 { 0, 0, -LINE_WIDTH },
  glm::vec3 { 0, LINE_WIDTH, 0 },
  glm::vec3 { 0, LINE_WIDTH, -LINE_LEN },
  glm::vec3 { 0, -LINE_WIDTH, -LINE_LEN },
  glm::vec3 { 0, -LINE_WIDTH, 0 }
};
unsigned int axis_vertices_vao_id;
unsigned int axis_vertices_vbo_id;

Material axis_materials[] = {
  Material { nullptr, glm::vec4 { 1.0f, 0.0f, 0.0f, 1.0f } },
  Material { nullptr, glm::vec4 { 0.0f, 1.0f, 0.0f, 1.0f } },
  Material { nullptr, glm::vec4 { 0.0f, 0.0f, 1.0f, 1.0f } },
  Material { nullptr, glm::vec4 { 0.5f, 0.0f, 0.0f, 1.0f } },
  Material { nullptr, glm::vec4 { 0.0f, 0.5f, 0.0f, 1.0f } },
  Material { nullptr, glm::vec4 { 0.0f, 0.0f, 0.5f, 1.0f } }
};

double cameraLocation = 0;
int view_dist = 1000;
glm::vec3 cameraPos = { 0.0f, 0.0f, -20.0f };

int display_mode = 0;

float camera_r = 20, camera_y = 2, camera_phi = 0, camera_theta = 0;

std::string map_file_path;

GLFWwindow *main_window;

static void draw_load_info(std::string msg, int percent) {
  glfwPollEvents();

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);

  if (ImGui::Begin("Fullscreen window", nullptr, flags)) {
    auto windowSize = ImGui::GetWindowSize();
    auto textSize = ImGui::CalcTextSize(msg.c_str());
    ImGui::SetCursorPos({ (windowSize.x - textSize.x) / 2, (windowSize.y - textSize.y) / 2 });
    ImGui::Text(msg.c_str());
  }

  ImGui::End();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwSwapBuffers(main_window);
}

static void load_game(GLFWwindow *window, std::string path, int loadFlag) {
  if (path.empty()) return;
  map_file_path = path;
  main_window = window;
  bmets::game::loader_progress_callback = draw_load_info;

  if (bmets::game::load(path, loadFlag) != 0) {
    display_mode = 1;
  } else {
    display_mode = 0;
  }
}


void SceneMain::setup(GLFWwindow* window) {

  mainShader = std::make_unique<Shader>("shaders/demo.vert", "shaders/demo.frag");
  mainShader->bind();

  acquire_uniform_locations(mainShader.get());

  ulViewMat = mainShader->getUniformLocation("view");
  ulProjMat = mainShader->getUniformLocation("projection");

  glGenVertexArrays(1, &axis_vertices_vao_id);
  glBindVertexArray(axis_vertices_vao_id);
  glGenBuffers(1, &axis_vertices_vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, axis_vertices_vbo_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(axis_vertices), &axis_vertices[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);	
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
  glVertexAttrib3f(1, 0.0f, 0.0f, 0.0f);
  glVertexAttrib2f(2, 0.0f, 0.0f);
  glVertexAttrib4f(4, 1.0f, 0.0f, 0.0f, 0.0f);
  glVertexAttrib4f(5, 0.0f, 1.0f, 0.0f, 0.0f);
  glVertexAttrib4f(6, 0.0f, 0.0f, 1.0f, 0.0f);
  glVertexAttrib4f(7, 0.0f, 0.0f, 0.0f, 1.0f);

  // mapScript.load("F:/SharedUserWorkData/Documents/BveTs/Scenarios/shuttle/hrd/route/0756/map_0756a.txt");
  // load_game(window, "F:/SharedUserWorkData/Documents/BveTs/Scenarios/mackoy.Keisei/Map.txt", 0);
};

void SceneMain::hide(GLFWwindow* window) {
  glDeleteBuffers(1, &axis_vertices_vbo_id);
  glDeleteVertexArrays(1, &axis_vertices_vao_id);
}

int vWidth, vHeight;

double lastTime = 0; int nbFrames = 0; double fps = 0;

ImGui::FileBrowser fileDialog;

void SceneMain::loop(GLFWwindow* window, double elapsedTime) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (display_mode == 0) {
  const float cameraSpeed = 0.2f; // adjust accordingly
  const float cameraSpeedAngle = 0.02f;
  if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
      //camera_r -= cameraSpeed;
      camera_y += cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
      //camera_r += cameraSpeed;
      camera_y -= cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      camera_phi += cameraSpeedAngle;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      camera_phi -= cameraSpeedAngle;
  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
      camera_theta -= cameraSpeedAngle;
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
      camera_theta += cameraSpeedAngle;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      cameraLocation += 1.0f;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      cameraLocation -= 1.0f;
  glm::vec3 trackPos = bmets::game::map.track_main.pos_at(cameraLocation);
  double trackTheta = bmets::game::map.track_main.l_spline.dir_at(cameraLocation);
  double cameraPhi = camera_phi - trackTheta;

  /*
  cameraPos = glm::vec3 { 
    cos(camera_theta) * sin(cameraPhi) * camera_r + trackPos.x, 
    -sin(camera_theta) * camera_r + trackPos.y,
    cos(camera_theta) * cos(cameraPhi) * camera_r + trackPos.z
  };
  glm::mat4 view = glm::lookAt(cameraPos, trackPos, glm::vec3 {0, 1, 0}); 
  mainShader->setUniform(ulViewMat, view);
  */
  glm::vec3 cameraPos1 = glm::vec3 { trackPos.x, trackPos.y + camera_y, trackPos.z};
  glm::vec3 cameraPos2 = glm::vec3 { 
    cos(camera_theta) * sin(cameraPhi + 3.14159) + cameraPos1.x, 
    -sin(camera_theta) + cameraPos1.y,
    cos(camera_theta) * cos(cameraPhi + 3.14159) + cameraPos1.z
  };
  glm::mat4 view = glm::lookAt(cameraPos1, cameraPos2, glm::vec3 {0, 1, 0}); 
  mainShader->setUniform(ulViewMat, view);

  /*glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  
  glBindVertexArray(axis_vertices_vao_id);
  for (int i = 0; i < 6; i++) {
    axis_materials[i].bind();
    glLineWidth(2.0);
    glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
  }*/

  glEnable(GL_CULL_FACE);

  glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (float)vWidth/(float)vHeight, 0.1f, (float)view_dist);
  mainShader->setUniform(ulProjMat, projMat);

  glDisable(GL_DEPTH_TEST);
  glm::mat4 bgMat = glm::translate(bmets::game::map.track_main.pos_at(cameraLocation) + glm::dvec3 { 0, camera_y, 0 });
  auto bgModel = bmets::game::map.track_main.bg_spline.value_at(cameraLocation);
  if (bgModel != nullptr) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    bgModel->draw(bgMat, Texture::PRIORITY_OPAQUE);
    bgModel->draw(bgMat, Texture::PRIORITY_ALPHA);
  }

  glEnable(GL_DEPTH_TEST);
  //model_manager.draw_all(cameraLocation, cameraLocation + view_dist);
  model_manager.draw_all(0);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  bool begin_load = false; int loadFlag = 0; std::string loadPath;
  if(ImGui::Begin("Information")) {
    double currentTime = glfwGetTime();
    if ( currentTime - lastTime >= 1.0 ) {
        fps = double(nbFrames) / ((currentTime - lastTime) / 1.0);
        nbFrames = 0;
        lastTime += 1.0;
    }
    nbFrames++;
    ImGui::Text("FPS: %d", (int)fps);
    ImGui::Text("Draw Calls / Frame: %d", bmets::render::model_manager.draw_call_count);

    ImGui::InputDouble("Location", &cameraLocation, 1, 100, "%.0f");
    ImGui::SliderInt("View Distance", &view_dist, 200, 10000);

    ImGui::Text("Total time / ms   : %d", timer.total);
    ImGui::Text("Parsing (ANTLR)   : %d", timer.durations[TIMER_PARSE_ANTLR]);
    ImGui::Text("Parsing (Execute) : %d", timer.durations[TIMER_PARSE_EXEC]);
    ImGui::Text("Parsing (Apply)   : %d", timer.durations[TIMER_PARSE_APPLY]);
    ImGui::Text("Model Loading     : %d", timer.durations[TIMER_MODEL]);
    ImGui::Text("Texture Loading   : %d", timer.durations[TIMER_TEXTURE]);
    //ImGui::Text("Instance VBO      : %d", timer.durations[TIMER_MODEL_INSTANCE]);
    ImGui::Spacing();
    ImGui::Text("Total Models      : %d", model_manager.model_lists.size());
    ImGui::Text("Alpha Models      : %d", model_manager.alpha_lists.size());

    ImGui::Separator();
    if(ImGui::Button("Open Map")) {
      std::string file = OpenFileDialog();
      if (!file.empty()) {
        loadPath = file;
        loadFlag = bmets::game::LOAD_ALL;
        begin_load = true;
      }
    }
    if (ImGui::Button("Open Keisei Chiba Line")) {
      loadPath = "/home/nemo/文档/BveTs/Scenarios/mackoy.Keisei/Map.txt";
      loadFlag = bmets::game::LOAD_ALL;
      begin_load = true;
    }
    ImGui::Spacing();
    if (ImGui::Button("Quick Reload")) {
      loadPath = map_file_path;
      loadFlag = bmets::game::LOAD_SKIP_STRUCTURE;
      begin_load = true;
    }
    if (ImGui::Button("Full Reload")) {
      loadPath = map_file_path;
      loadFlag = bmets::game::LOAD_ALL;
      begin_load = true;
    }

    fileDialog.SetTypeFilters({ ".txt" });
    fileDialog.Display();
    if(fileDialog.HasSelected()) {
      loadPath = fileDialog.GetSelected().string();
      loadFlag = bmets::game::LOAD_ALL;
      begin_load = true;
      fileDialog.ClearSelected();
    }
  }

  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (begin_load) load_game(window, loadPath, loadFlag);

  } else if (display_mode == 1) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    if (ImGui::Begin("Fullscreen window", nullptr, flags)) {
      if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS 
        || glfwGetKey(window, GLFW_KEY_KP_ENTER) == GLFW_PRESS
        || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        display_mode = 0;
      }
      if (ImGui::Button("Continue")) {
        display_mode = 0;
      }
      ImGui::Separator();

      if (!bmets::game::loader_exception.message.empty()) {
        ImColor red(255, 0, 0);
        ImGui::TextColored(red, "An non-recoverable error has occured and the map failed to load.");
        auto err = bmets::game::loader_exception;
        ImGui::TextUnformatted(err.message.c_str());
        ImGui::Spacing();
      }

      if (bmets::game::loader_warnings.size() > 0) {
        ImGui::Text("Some issues are found during loading. The map might not display correctly.");
      }
      ImGui::Columns(2);
      ImGui::SetColumnWidth(0, 100);
      for (auto &warnList : bmets::game::loader_warnings) {
        ImGui::Text("File:");
        ImGui::NextColumn();
        ImGui::TextUnformatted(warnList.first.c_str());
        ImGui::NextColumn();
        for (auto &warn : warnList.second) {
          if (warn.line >= 0) {
            ImGui::Text("  L %d", warn.line);
          } else {
            ImGui::Text("  -");
          }
          ImGui::NextColumn();
          ImGui::TextUnformatted(warn.message.c_str());
          ImGui::NextColumn();
        }
      }
      ImGui::Columns();
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
};

void SceneMain::update_viewport(int width, int height) {
  vWidth = width; vHeight = height;
}