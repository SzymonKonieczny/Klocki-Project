#include "Enitity.h"
#include "World.h"
Entity::Entity(glm::vec3 Pos, World* wrld) : world(wrld), Position(Pos)
{
}