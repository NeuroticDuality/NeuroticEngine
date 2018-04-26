#ifndef RENDER_H_
#define RENDER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GL/glew.h"
#include "stdio.h"

#include "shader.hpp"
#include "physics.hpp"
#include "chunk.hpp"

class Render{
public:
Render();

unsigned int NumVerts, NumDraw, NumTexBind;
void LoadTexture(Shader* shader, char* FileLocation, int ID);
void AssignTextures(Shader* shader);
void DrawQuad(Shader* shader, Physics* physics, int ID);
void DrawCube(Shader* shader, Physics* physics, int BottID, int SideID, int TopID);
void DrawObjects(Shader* shader, Physics* physics, ChunkManager* chunkmanager);
void DrawIntro(Shader* shader, Physics* physics);
void DrawChunk(Shader* shader, Physics* physics, ChunkManager* chunkmanager, int ChunkX, int ChunkZ);
void DrawFrog(Shader* shader, Physics* physics);
void DrawBlocks(Shader* shader, Physics* physics);

GLuint QuadVBO, QuadVAO, QuadEBO;
GLuint CubeVBO, CubeVAO, CubeEBO;

SDL_Surface* TexSurf;
GLuint TexID[128];
};

#endif
