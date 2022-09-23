#pragma once
#include "BlockTemplate.h"
#include "Util.h"
class Mesh;


class FaceBuilder
{
public:
	static void BuildFace(Mesh& verticies, Faces Direction, glm::vec3 Pos, BlockTypes block, BlockShapes Shape);

};