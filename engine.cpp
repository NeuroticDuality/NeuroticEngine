#include "engine.hpp"

int EngineStart()
{
//Initalize objects and default values.
Display* display = new(Display);
Shader* shader = new(Shader);
Render* render = new(Render);
Eventsystem* eventsystem = new(Eventsystem);
Physics* physics = new(Physics);

shader->GenerateShaders();
render->AssignTextures(shader);
glUseProgram(shader->ShaderProgram);

char QuitIntro = 0;
eventsystem->AllowUserInput = 0;
//IntroLoop
while(QuitIntro)
{
display->ClearScreen(glm::vec4(0.22f, 0.43f, 0.64f, 1.0f));
render->DrawIntro(shader, physics);
SDL_GL_SwapWindow(display->Window);
eventsystem->HandleEvents();
physics->UpdateObjects(shader, eventsystem);
eventsystem->CapFPS();
//Start GameLoop if 3 seconds have passed.
if(physics->RotTimer > 3)
{
QuitIntro = 1;
eventsystem->AllowUserInput = 1;
}

}

//GameLoop
while(!eventsystem->Quit)
{

//Clear screen sky blue then Draw Objects.
display->ClearScreen(glm::vec4(0.22f, 0.43f, 0.64f, 1.0f));
render->DrawObjects(shader, physics);
//Swap Window buffer.
SDL_GL_SwapWindow(display->Window);
//Handle all input and then update relevnt objects.
eventsystem->HandleEvents();
physics->UpdateObjects(shader, eventsystem);
//Vsync 60fps
eventsystem->CapFPS();
}

return 0;
}
