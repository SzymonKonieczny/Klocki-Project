#pragma once
#include "Enitity.h"
#include "Collider.h"
#include "EntityMesh.h"
#include "Util.h"
#include "Block.h"
class ProtoAnimal : public Entity, Collider
{

	EntityMesh mesh;
public:
	unsigned int id;
	glm::vec3 TargetPos;
	bool reacherdTarget = true;
	ProtoAnimal(unsigned int ID, World* wrld, glm::vec3 Pos);
	void Draw(Shader& shader);
	void Tick(float dt);



};
