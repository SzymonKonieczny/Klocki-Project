#include "Collider.h"
#include "World.h"
#include "Chunk.h"

Collider::Collider(glm::vec3 MinBounds_, glm::vec3 MaxBounds_) : MinBounds(MinBounds_), MaxBounds(MaxBounds_)
{
	minX= MinBounds_.x;
	minY= MinBounds_.y;
	minZ= MinBounds_.z;

	maxX=MaxBounds_.x;
	maxY=MaxBounds_.y;
	maxZ=MaxBounds_.z;
}

bool Collider::checkCollision(glm::vec3 Position, World* world)
{
	glm::vec3 OffsetPosition;


	OffsetPosition = Position + glm::vec3(minX, minY, minZ);	//left back bottom
	 if (CheckPoint(OffsetPosition, world)) return true;

	 OffsetPosition = Position + glm::vec3(maxX, minY, minZ);	//right back bottom
	 if (CheckPoint(OffsetPosition, world)) return true;

	 OffsetPosition = Position + glm::vec3(minX, minY, maxZ);	//left front bottom
	 if (CheckPoint(OffsetPosition, world)) return true;

	 OffsetPosition = Position + glm::vec3(maxX, minY, maxZ);	//right front bottom
	 if (CheckPoint(OffsetPosition, world)) return true;

	 OffsetPosition = Position + glm::vec3(minX, maxY, minZ);	//left back up
	 if (CheckPoint(OffsetPosition, world)) return true;

	 OffsetPosition = Position + glm::vec3(maxX, maxY, minZ);	//right back up
	 if (CheckPoint(OffsetPosition, world)) return true;

	 OffsetPosition = Position + glm::vec3(minX, maxY, maxZ);	//left front up
	 if (CheckPoint(OffsetPosition, world)) return true;

	 OffsetPosition = Position + glm::vec3(maxX, maxY, maxZ);	//right front up
	 if (CheckPoint(OffsetPosition, world)) return true;

	return false;
}

bool Collider::CheckPoint(glm::vec3 OffsetPosition, World* world, bool CollidableOnly)
{
	auto chunkptr = world->chunkMenager.GetChunkAt(Util::WorldPosToChunkPos(OffsetPosition));
	if (chunkptr != nullptr)
	{
		chunkptr->LockBlockMutex();
		Block* b = chunkptr->vec3ToBlock(Util::WorldPosToLocalPos(OffsetPosition));
		chunkptr->UnlockBlockMutex();

		if (b != nullptr)
		{
			if(CollidableOnly && Util::GetInstance()->BLOCKS[b->ID].Collidable) return true;
			else if (!CollidableOnly && Util::GetInstance()->BLOCKS[b->ID].Selectable) return true;
		}
		//if (b != nullptr && CollidableOnly && Util::GetInstance()->BLOCKS[b->ID].Collidable) return true;
		//else if (b != nullptr && Util::GetInstance()->BLOCKS[b->ID].Selectable) return true;
	}

	return false;
}
