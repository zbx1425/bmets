#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
  Shader(const char* pathSrcVertex, const char* pathSrcFragment);

  void bind() {
    if (activeId != id) {
      glUseProgram(id);
      activeId = id;
    }
  }

  int getUniformLocation(const char* name) {
    bind();
    return glGetUniformLocation(id, name);
  }

  void setUniform(int location, bool value) {
    bind();
    glUniform1i(location, (int)value);
  }

  void setUniform(int location, int value) {
    bind();
    glUniform1i(location, value);
  }

  void setUniform(int location, float value) {
    bind();
    glUniform1f(location, value);
  }

  void setUniform(int location, glm::mat4 value)  {
    bind();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
  }

  ~Shader() {
    glDeleteProgram(id);
  }

private:
  unsigned int id;
  static unsigned int activeId;
};
