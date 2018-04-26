#ifndef SHADER_H
#define SHADER_H

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include <iostream>

class Shader{
public:
  GLuint VertexShader;
  GLuint FragmentShader;
  GLuint ShaderProgram;
  int Success;
  char* Log;
  int CurrentTexture;
  int GenerateShaders();
};



#endif
