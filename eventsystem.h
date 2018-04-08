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
char Quit = 0;
char Key_W = 0;
char Key_A = 0;
char Key_S = 0;
char Key_D = 0;
char Key_Space = 0;
char Key_LShift = 0;
char ScrollWheelY = 0;
//Track DeltaTime.
float DeltaTime = 0;
unsigned int LastFrameTime = 0, CurrentFrameTime = 0;
//Mouse Position change relative every frame.
int MouseXRelative = 0, MouseYRelative = 0;

char AllowUserInput = 0;
};

#endif
