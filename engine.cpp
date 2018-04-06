#include "engine.hpp"

int EngineStart()
{
//Initalize objects and default values.
    Display* display = new(Display);
    Shader* shader = new(Shader);
    Render* render = new(Render);
    Eventsystem* eventsystem = new(Eventsystem);

    shader->GenerateShaders();

    while(!eventsystem->Quit)
    {
//Handle all input and then update relevnt objects.
    eventsystem->HandleEvents();
//Select Correct Shaders then Draw Objects.
    display->ClearScreen();
    glUseProgram(shader->ShaderProgram);
    render->DrawObjects();
    SDL_GL_SwapWindow(display->Window);
//Vsync 60fps
    eventsystem->CapFPS();
    }

return 0;
}
