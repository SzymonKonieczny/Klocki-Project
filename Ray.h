#pragma once
#include <glm/glm.hpp>
class World;

struct RayInfo
{
	glm::vec3 HitPos;
	glm::vec3 HitFromPos;
	bool Miss;

};
class Ray
{

public:
	static RayInfo Cast(glm::vec3 Start, glm::vec3 Direction,World* world, float distance);

	

};