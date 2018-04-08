#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.hpp"
#include "eventsystem.h"

#include "stdio.h"

class Physics{
public:
Physics();

void UpdateObjects(Shader* shader, Eventsystem* eventsystem);

glm::mat4 Model, View, Proj;

glm::vec3 FrogPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 FrogSpeed = glm::vec3(10.0f, 25.0f, 0.0f);

float RotTimer = 0;
};

#endif
