#include "display.hpp"

void Display::ClearScreen(glm::vec4 ScreenColor)
{
    glClearColor(ScreenColor.x, ScreenColor.y, ScreenColor.z, ScreenColor.w);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

Display::Display()
{
//Init SDL's video and event sub-systems.
    SDL_Init(SDL_INIT_EVERYTHING);
//Set GL version (3.3).
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//Create Window with default values.
    Window = SDL_CreateWindow("NeuroticEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

//Set OpenGL Context to SDL's Window.
    GLContext = SDL_GL_CreateContext(Window);

//Init glew to use core OpenGL functionality.
    glewExperimental = GL_TRUE;
    glewInit();
//Set viewport to size of window.
    glViewport(0, 0, GetWindowX(), GetWindowY());

}

int Display::GetWindowX()
{
  int x;
  SDL_GL_GetDrawableSize(Window, &x, 0);
  return x;
}

int Display::GetWindowY()
{
  int y;
  SDL_GL_GetDrawableSize(Window, 0, &y);
  return y;
}

int Display::GetScreenX()
{
  SDL_DisplayMode dm;
  if (SDL_GetDesktopDisplayMode(0, &dm));
  return dm.w;
}

int Display::GetScreenY()
{
  SDL_DisplayMode dm;
  if (SDL_GetDesktopDisplayMode(0, &dm));
  return dm.h;
}
