#pragma once
#include "BlockTemplate.h"
#include "Util.h"

template<typename T>
class Mesh;
class FaceBuilder
{
public:
	static void BuildFace(Mesh<CompressedVertex>& verticies, Faces Direction, glm::vec3 Pos, BlockTypes block, BlockShapes Shape);

};