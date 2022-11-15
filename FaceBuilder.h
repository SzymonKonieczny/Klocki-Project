#pragma once
#include "BlockTemplate.h"
#include "Util.h"
template<typename T>
class Mesh<T>;

template<typename T>
class FaceBuilder
{
public:
	static void BuildFace(Mesh<T>& verticies, Faces Direction, glm::vec3 Pos, BlockTypes block, BlockShapes Shape);

};