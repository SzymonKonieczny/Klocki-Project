#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>
#include <memory>
#include "Enitity.h"

class World;
class EntityMenager
{
	World* world;
	unsigned int highestID = 0;
public:
	std::unordered_map<unsigned , std::shared_ptr<Entity>> EntityMap;
	EntityMenager(World* wrld);

	void SpawnEntity(glm::vec3 Pos, EntityTypes type); //Unsure of how to pass in what type of an entity we want. Enum seems lengthy



};
