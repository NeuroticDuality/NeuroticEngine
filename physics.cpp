#include "physics.hpp"

Physics::Physics(){
RotTimer = 0.0f;
//Set Default MVP values.
Model = glm::mat4();
View = glm::mat4();
Proj = glm::mat4();
//Set Perspective.
Proj = glm::perspective(glm::radians(90.0f), (1280.0f / 720.0f), 0.1f, 256.0f);
FrogPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Physics::UpdateObjects(Shader* shader, Eventsystem* eventsystem){
//Update Counters.
RotTimer += eventsystem->DeltaTime;
//Update Camera.
//glm::vec3 CamDir = glm::normalize(CamPos - CamTarg);
//glm::vec3 UpDir = glm::vec3(0.0f, 1.0f, 0.0f);
//glm::vec3 CameraRight = glm::normalize(glm::cross(UpDir, CamDir));

CamYaw   += 0.25 * (eventsystem->MouseXRelative);
CamPitch += 0.25 * (eventsystem->MouseYRelative);

if(CamPitch > 89.0f)CamPitch =  89.0f;
if(CamPitch < -89.0f)CamPitch = -89.0f;

glm::vec3 front;
front.x = cos(glm::radians(CamPitch)) * cos(glm::radians(CamYaw));
front.y = sin(glm::radians(CamPitch));
front.z = cos(glm::radians(CamPitch)) * sin(glm::radians(CamYaw));
CamForward = glm::normalize(front);

View = glm::lookAt(CamPos, CamPos + CamForward, CamUp);
//Update Camera.

CamVel += ((eventsystem->Key_W * FrogSpeed.y) * CamForward) * eventsystem->DeltaTime;
CamVel -= ((eventsystem->Key_A * FrogSpeed.y) * glm::normalize(glm::cross(CamForward, CamUp))) * eventsystem->DeltaTime;
CamVel -= ((eventsystem->Key_S * FrogSpeed.y) * CamForward) * eventsystem->DeltaTime;
CamVel += ((eventsystem->Key_D * FrogSpeed.y) * glm::normalize(glm::cross(CamForward, CamUp))) * eventsystem->DeltaTime;

CamVel *= 0.8;

CamPos += CamVel;

CamPos += ((eventsystem->Key_Space * FrogSpeed.y) * CamUp) * eventsystem->DeltaTime;
CamPos -= ((eventsystem->Key_LShift * FrogSpeed.y) * CamUp) * eventsystem->DeltaTime;

fprintf(stderr, "CamPos Vec3(%f, %f, %f)\n", CamPos.x, CamPos.y, CamPos.z);
fprintf(stderr, "CamVel Vec3(%f, %f, %f)\n", CamVel.x, CamVel.y, CamVel.z);
fprintf(stderr, "CamPitch(%f)\n", CamPitch);
fprintf(stderr, "CamYaw(%f)\n", CamYaw);
fprintf(stderr, "RotTimer:%f\n", RotTimer);
fprintf(stderr, "DeltaTime:%f\n", eventsystem->DeltaTime);

glm::mat4 MVP = Proj * View * Model;
//SetShader MVP
glUseProgram(shader->ShaderProgram);
GLint UniformMVP = glGetUniformLocation(shader->ShaderProgram, "MVP");
glUniformMatrix4fv(UniformMVP, 1 , GL_FALSE, glm::value_ptr(MVP));
}
