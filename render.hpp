#ifndef RENDER_H_
#define RENDER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GL/glew.h"
#include "stdio.h"

#include "shader.hpp"
#include "physics.hpp"

class Render{
public:
Render();

void LoadTexture(Shader* shader, char* FileLocation, int ID);
void AssignTextures(Shader* shader);

void DrawObjects(Shader* shader, Physics* physics);
void DrawIntro(Shader* shader, Physics* physics);
void DrawFrog(Shader* shader, Physics* physics);
void DrawBlocks(Shader* shader, Physics* physics);

GLuint QuadVBO, QuadVAO, QuadEBO;
GLuint CubeVBO, CubeVAO, CubeEBO;

SDL_Surface* TexSurf;
GLuint TexID[24];
};

#endif
