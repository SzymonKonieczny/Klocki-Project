#include "ProtoAnimal.h"
#include "World.h"
ProtoAnimal::ProtoAnimal(unsigned int ID, World* wrld, glm::vec3 Pos) :
	Collider(glm::vec3(-0.25, 0, -0.25),	glm::vec3(0.25, 0.9, 0.25)), Entity( Pos, wrld), id(ID)
{
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(-0.3f, 0.0, -0.3f),
			glm::vec3(0.1f, 0.2f, 0.3f),
			glm::vec2(1, 0)));
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(0.3f, 0.0, -0.3f),
			glm::vec3(0.1f, 0.2f, 0.3f),
			glm::vec2(1, 1)));
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(0.3f, 0.0, 0.3f),
			glm::vec3(0.1f, 0.2f, 0.3f),
			glm::vec2(0, 0)));
	mesh.verticiesSetReady();

}
void ProtoAnimal::Draw(Shader& shader)
{
	mesh.Draw(shader, Position, true);
}

void ProtoAnimal::Tick(float dt)
{
	if (!reacherdTarget)
	{
		glm::vec3 dir = glm::normalize(TargetPos - Position);
		if(!checkCollision(dir * 0.1f * dt, world))
		Position += dir * 0.1f * dt;

		if (glm::distance(Position, TargetPos) < 0.4) reacherdTarget = true;

	}
	else
	{
		int diffx = Util::GetInstance()->random(3,10);
		int diffz = Util::GetInstance()->random(3, 10);
		int diffy = Util::GetInstance()->random(-2, 2);

		glm::vec3 PosDif(diffx, diffy, diffz);
		Block* b = world->chunkMenager.GetBlockInWorld(PosDif + Position);
		if (b != nullptr && !Util::GetInstance()->BLOCKS[b->ID].Collidable)
		{
			b = world->chunkMenager.GetBlockInWorld(PosDif + Position + glm::vec3(0,-1,0));
			if (b != nullptr && Util::GetInstance()->BLOCKS[b->ID].Collidable)
			{
				TargetPos = PosDif + Position;
			}
		}

	}
}
