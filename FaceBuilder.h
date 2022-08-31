#pragma once
#include "BlockTemplate.h"
#include "Util.h"

class FaceBuilder
{
public:
	static void BuildFace(std::vector<Vertex>& vertices, Faces Direction, glm::vec3 Pos, BlockTypes block = BlockTypes::Grass);

};