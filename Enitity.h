#pragma once
#include "shaderClass.h"
#include "Libraries/include/glm/glm.hpp"
class World;

enum EntityTypes
{
	Proto

};

class Entity
{
public:
	glm::vec3 Position;
	World* world;
	virtual void Draw(Shader& shader) = 0;
	virtual void Tick(float dt) = 0;
	Entity(glm::vec3 Pos, World* wrld);

};