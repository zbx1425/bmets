#pragma once

typedef struct GLFWwindow GLFWwindow;

class Scene {
public:
  Scene() {};
  virtual void setup(GLFWwindow* window) = 0;
  virtual void hide(GLFWwindow* window) = 0;
  virtual void loop(GLFWwindow* window, double elapsed_time) = 0;
  virtual void update_viewport(int width, int height) = 0;
  virtual ~Scene() {};
};