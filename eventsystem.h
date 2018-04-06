#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include "SDL2/SDL.h"
#include "stdio.h"

class Eventsystem{
public:

void SetDeltaTime();
void HandleEvents();
void CapFPS();

SDL_Event Event;
//Keys.
char Quit = 0, Key_W, Key_A, Key_S, Key_D, Key_Space, Key_LShift, ScrollWheelY;
//Track DeltaTime.
float DeltaTime;
unsigned int LastFrameTime, CurrentFrameTime;
//Mouse Position change relative every frame.
int MouseXRelative, MouseYRelative;
};

#endif
