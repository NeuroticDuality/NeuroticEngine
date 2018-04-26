#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.hpp"
#include "eventsystem.h"
#include "chunk.hpp"

#include "stdio.h"

class Physics{
public:
Physics();

void UpdateObjects(Shader* shader, Eventsystem* eventsystem);

glm::mat4 Model, View, Proj;

//Camera
float CamYaw = -90.0f;
float CamPitch = 0.0f;
glm::vec3 CamVel =  glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 CamPos =  glm::vec3(0.0f, 0.0f, 2.5f);
glm::vec3 CamForward = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 CamUp    = glm::vec3(0.0f, 1.0f,  0.0f);
//Target
glm::vec3 CamTarg = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 FrogPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 FrogSpeed = glm::vec3(5.0f, 12.5f, 0.0f);

float RotTimer = 0;
};

#endif
