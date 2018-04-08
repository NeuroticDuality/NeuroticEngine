#include "physics.hpp"

Physics::Physics()
{
RotTimer = 0.0f;
//Set Default MVP values.
Model = glm::mat4();
View = glm::mat4();
Proj = glm::mat4();
//View = glm::lookAt(
//glm::vec3(2.5f, 2.5f, 2.0f),
//glm::vec3(0.0f, 0.0f, 0.0f),
//glm::vec3(0.0f, 0.0f, 1.0f));

Proj = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 100.0f);
FrogPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Physics::UpdateObjects(Shader* shader, Eventsystem* eventsystem)
{
//Update Counters.
RotTimer += eventsystem->DeltaTime;
//Update MVP Components.
FrogPos.y += (eventsystem->Key_W * FrogSpeed.y) * eventsystem->DeltaTime;
FrogPos.x -= (eventsystem->Key_A * FrogSpeed.x) * eventsystem->DeltaTime;
FrogPos.y -= (eventsystem->Key_S * FrogSpeed.y) * eventsystem->DeltaTime;
FrogPos.x += (eventsystem->Key_D * FrogSpeed.x) * eventsystem->DeltaTime;

View = glm::mat4();
View = glm::translate(View, glm::vec3(0.0f, 0.0f, -5.0f));
fprintf(stderr,"FrogBro Vec3(%f, %f, %f)\n", FrogPos.x, FrogPos.y, FrogPos.z);
fprintf(stderr, "RotTimer:%f\n", RotTimer);
//Model = glm::scale(Model, glm::vec3(100.0f, 100.0f, 1.0f));

//Combine MVP and send to vertex shader.

}
