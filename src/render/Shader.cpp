#include <glad/glad.h>
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

unsigned int Shader::activeId;

Shader::Shader(const char* pathSrcVertex, const char* pathSrcFragment) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  vShaderFile.open(pathSrcVertex);
  fShaderFile.open(pathSrcFragment);
  std::stringstream vShaderStream, fShaderStream;
  vShaderStream << vShaderFile.rdbuf();
  fShaderStream << fShaderFile.rdbuf();
  vShaderFile.close();
  fShaderFile.close();
  vertexCode = vShaderStream.str();
  fragmentCode = fShaderStream.str();
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  unsigned int vertex, fragment;
  int success;
  char infoLog[512];
  
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if(!success) {
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      std::cerr << "Cannot compile vertex Shader: \n" << infoLog << std::endl;
  };
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if(!success) {
      glGetShaderInfoLog(fragment, 512, NULL, infoLog);
      std::cerr << "Cannot compile fragment Shader: \n" << infoLog << std::endl;
  };
    
  id = glCreateProgram();
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  glLinkProgram(id);
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(id, 512, NULL, infoLog);
      std::cerr << "Cannot link Shader program: \n" << infoLog << std::endl;
  }
  
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}