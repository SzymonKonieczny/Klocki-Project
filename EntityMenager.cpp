#include "EntityMenager.h"
#include "ProtoAnimal.h"
EntityMenager::EntityMenager(World* wrld) : world(wrld)
{

}

void EntityMenager::SpawnEntity(glm::vec3 Pos, EntityTypes type)
{
	switch (type)
	{
	case Proto:
		EntityMap.try_emplace(highestID, std::make_shared<ProtoAnimal>(highestID, world, Pos));
		
		break;
	default:
		break;
	}

	highestID++;
}
