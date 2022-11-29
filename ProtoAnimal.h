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
	float speed = 3;
	unsigned int id;
	glm::vec3 TargetPos;
	glm::vec3 PrevPosition[2];
	glm::vec3 velocity;
	bool reacherdTarget = true;
	ProtoAnimal(unsigned int ID, World* wrld, glm::vec3 Pos);
	void Draw(Shader& shader);
	void Tick(float dt) override ;
	bool HandleCollisions(glm::vec3 &Velocity);
	bool CheckCollisionSide(glm::vec3 dir);
	


private:
	bool comparePrevPositions();

};
