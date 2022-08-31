#include "BlockSelectMesh.h"

void BlockSelectMesh::Generate()
{
	vertices = {
			{ glm::vec3(0.0f,   0.0f, 1.0f),
				 glm::vec3(1.0f, 1.0f, 1.0f),
				 glm::vec2(0,1) },
			{ glm::vec3(1.0f,   0.0f, 1.0f),
				 glm::vec3(1.0f, 1.0f, 1.0f),
				 glm::vec2(1 , 1) },
			{ glm::vec3(1.0f,  -1.f, 1.0f),
				 glm::vec3(1.0f, 1.0f, 1.0f),
				 glm::vec2(1 , 0) },
			{ glm::vec3(0.0f,  -1.f, 1.0f),
				 glm::vec3(1.0f, 1.0f, 1.0f),
				 glm::vec2(0,0)},
	};
	indices = { 0,1,2,3,2,0 };

}
