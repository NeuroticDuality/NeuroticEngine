#include "eventsystem.h"

void Eventsystem::SetDeltaTime()
{
  //Get ticks since SDL_Init() was called, DeltaTime = ticks between LastFrameTime and CurrentFrameTime.
  CurrentFrameTime = SDL_GetTicks();
  DeltaTime = (float)(CurrentFrameTime - LastFrameTime) / 1000;
  LastFrameTime = CurrentFrameTime;
}

void Eventsystem::HandleEvents()
{
//Get delta time.
  SetDeltaTime();
//Reset values.
  MouseYRelative = 0;
  MouseXRelative = 0;
  ScrollWheelY = 0;

//Poll events and set values accordingly.
  while(SDL_PollEvent(&Event))
  {
    if (Event.type == SDL_MOUSEMOTION)
    {
    MouseXRelative =  Event.motion.xrel;
    MouseYRelative = -Event.motion.yrel;
    }
  switch(Event.type)
      {
        case SDL_QUIT:
        Quit = 1;
        break;

        case SDL_KEYDOWN:
          switch(Event.key.keysym.sym)
          {
          case SDLK_ESCAPE:
          Quit = 1;
          break;
          case SDLK_w:
          Key_W = 1;
          break;
          case SDLK_a:
          Key_A = 1;
          break;
          case SDLK_s:
          Key_S = 1;
          break;
          case SDLK_d:
          Key_D = 1;
          break;
          case SDLK_SPACE:
          Key_Space = 1;
          break;
          case SDLK_LSHIFT:
          Key_LShift = 1;
          break;
          }
        break;

        case SDL_KEYUP:
          switch(Event.key.keysym.sym)
          {
          case SDLK_w:
          Key_W = 0;
          break;
          case SDLK_a:
          Key_A = 0;
          break;
          case SDLK_s:
          Key_S = 0;
          break;
          case SDLK_d:
          Key_D = 0;
          break;
          case SDLK_SPACE:
          Key_Space = 0;
          break;
          case SDLK_LSHIFT:
          Key_LShift = 0;
          break;
          }
        break;

        case SDL_MOUSEWHEEL:
          ScrollWheelY = Event.wheel.y;
      }
    }

}

void Eventsystem::CapFPS()
{
  if(DeltaTime < 1000 / 60) SDL_Delay(1000 / 60 - DeltaTime);
}
