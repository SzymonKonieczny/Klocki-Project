#include "ProtoAnimal.h"
ProtoAnimal::ProtoAnimal(int ID) :Collider(glm::vec3(-0.25,0,-0.25), glm::vec3(0.25, 0.9, 0.25)), id(ID)
{
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(-0.3f, 0.0, -0.3f),
			glm::vec3(0.1f, 0.2f, 0.3f),
			glm::vec2(1, 0.99)));
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(0.3f, 0.0, -0.3f),
			glm::vec3(0.1f, 0.2f, 0.3f),
			glm::vec2(1, 0.99)));
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(0.3f, 0.0, 0.3f),
			glm::vec3(0.1f, 0.2f, 0.3f),
			glm::vec2(1, 0.99)));

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
		Position += dir * 0.1f * dt;
	}
	else
	{

	}
}
