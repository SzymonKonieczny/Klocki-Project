#pragma once
#include "Enitity.h"
#include "Collider.h"
#include "EntityMesh.h"

class ProtoAnimal : public Entity, Collider
{

	EntityMesh mesh;
public:
	int id;
	glm::vec3 TargetPos;
	bool reacherdTarget = true;
	ProtoAnimal(int ID);
	void Draw(Shader& shader);
	void Tick(float dt);



};
