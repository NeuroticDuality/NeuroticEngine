#ifndef RENDER_H_
#define RENDER_H_

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "stdio.h"

class Render{
public:
Render();

void DrawObjects();

unsigned int VBO, VAO;
};

#endif
