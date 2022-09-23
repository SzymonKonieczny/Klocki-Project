#pragma once

#pragma once
#ifndef COLLIDER.H

#include <glm/glm.hpp>

#include "Util.h"

class World;
struct CollisionResult // for now unused
{
	bool doesIntersect;
	//bool IntersectsOnX;
	//bool IntersectsOnY;
	//bool IntersectsOnZ;

};
class Collider {
	glm::vec3 MinBounds, MaxBounds;
	float minX;
	float minY;
	float minZ;

	float maxX;
	float maxY;
	float maxZ;


public:

	Collider(glm::vec3 MinBounds_, glm::vec3 MaxBounds_);
	bool checkCollision(glm::vec3 Position, World* world );
	bool CheckPoint(glm::vec3 OffsetPosition, World* world);

};

#endif // !C