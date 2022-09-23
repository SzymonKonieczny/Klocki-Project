#include "Ray.h"
#include "World.h"
RayInfo Ray::Cast(glm::vec3 Start, glm::vec3 Direction, World* world, float distance)
{
	Direction = glm::normalize(Direction);
	RayInfo info;
	info.Miss = true;
	info.HitFromPos = Start;//glm::floor(Start);
	info.HitPos = Start;//;glm::floor(Start);

	for (float i = 0; i < distance; i += 0.1f)
	{
		info.HitFromPos = info.HitPos;
		info.HitPos = info.HitFromPos + (Direction * 0.1f);
		if (Collider::CheckPoint(info.HitPos,world,false))
		{
			//info.HitPos = glm::floor(info.HitPos + glm::vec3(1, 0,1));
			//info.HitFromPos = glm::floor(info.HitFromPos + glm::vec3(1, 0,1));
			info.HitPos = glm::floor(info.HitPos);
			info.HitFromPos = glm::floor(info.HitFromPos);
			info.Miss = false;
			return info;

		}


	}

	return info;
}
