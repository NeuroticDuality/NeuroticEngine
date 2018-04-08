#ifndef DISPLAY_H_
#define  DISPLAY_H_

#include "SDL2/SDL.h"
#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Display{
public:
Display();

void ClearScreen(glm::vec4 ScreenColor);

int GetWindowX();
int GetWindowY();

int GetScreenX();
int GetScreenY();

unsigned int WindowX = 640;
unsigned int WindowY = 480;

SDL_Window* Window;
SDL_GLContext GLContext;
};

#endif
