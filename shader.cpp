#include "shader.hpp"
#include "fragment.hpp"
#include "vertex.hpp"

int Shader::GenerateShaders()
{
//Allocate memory for shader error log.
  char Log[512];
//Assign VertexSource to VertexShader then compile.
  VertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(VertexShader, 1, VertexSource, 0);
  glCompileShader(VertexShader);
//Check for compilation errors.
  glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
  if(!Success)
  {
    glGetShaderInfoLog(VertexShader, 512, NULL, Log);
    printf("Vertex Compilation Failed:\n%s", Log);
    return 1;
  }
//Assign FragmentSource to FragmentShader then compile.
  FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(FragmentShader, 1, FragmentSource, 0);
  glCompileShader(FragmentShader);
//Check for compilation errors.
  glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
  if(!Success)
  {
    glGetShaderInfoLog(FragmentShader, 512, NULL, Log);
    printf("Fragment Compilation Failed:\n%s", Log);
    return 1;
  }
//Attach compiled Vertex and Fragment shaders to ShaderProgram.
  ShaderProgram = glCreateProgram();
  glAttachShader(ShaderProgram, VertexShader);
  glAttachShader(ShaderProgram, FragmentShader);
  glLinkProgram(ShaderProgram);
//Check for compilation errors.
  glGetShaderiv(ShaderProgram, GL_COMPILE_STATUS, &Success);
  if(!Success)
  {
    glGetShaderInfoLog(ShaderProgram, 512, NULL, Log);
    printf("Fragment Compilation Failed:\n%s", Log);
    return 1;
  }
//Detach and delete compiled shaders from ShaderProgram.
  glDetachShader(ShaderProgram, VertexShader);
  glDetachShader(ShaderProgram, FragmentShader);
//Delete leftover shader source objects.
  glDeleteShader(VertexShader);
  glDeleteShader(FragmentShader);
//Free Log's allocated memory.
  //delete(Log);
  return 0;
}
