#include "engine.hpp"

int EngineStart(){
//Initalize objects and default values.
Display* display = new(Display);
Shader* shader = new(Shader);
Render* render = new(Render);
Eventsystem* eventsystem = new(Eventsystem);
Physics* physics = new(Physics);
ChunkManager* chunkmanager = new(ChunkManager);

shader->GenerateShaders();
render->AssignTextures(shader);
glUseProgram(shader->ShaderProgram);

char QuitIntro = 0;
//IntroLoop
while(!QuitIntro){
display->ClearScreen(glm::vec4(0.1f, 0.0f, 0.0f, 1.0f));
render->DrawIntro(shader, physics);
SDL_GL_SwapWindow(display->Window);
eventsystem->HandleEvents();
physics->UpdateObjects(shader, eventsystem);
eventsystem->CapFPS();
//Start GameLoop if 3 seconds have passed.
if(eventsystem->Key_Space) QuitIntro = 1;
}

//GameLoop
while(!eventsystem->Quit){
//Clear screen sky blue then Draw Objects.
display->ClearScreen(glm::vec4(0.1f, 0.0f, 0.0f, 1.0f));
render->DrawObjects(shader, physics, chunkmanager);
//Swap Window buffer.
SDL_GL_SwapWindow(display->Window);
//Handle all input and then update relevnt objects.
eventsystem->HandleEvents();
physics->UpdateObjects(shader, eventsystem);
eventsystem->CapFPS();
}

return 0;
}
