#include "ProtoAnimal.h"
#include "World.h"
ProtoAnimal::ProtoAnimal(unsigned int ID, World* wrld, glm::vec3 Pos) :
	Collider(glm::vec3(-0.2, 0, -0.2),	glm::vec3(0.2, 0.9, 0.2)), Entity( Pos, wrld), id(ID)
{
	//Belly
	{ 
		mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(-0.3f, 0.0, -0.3f),
			glm::vec3(1, 1, 1),
			glm::vec2(0, 0)));
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(0.3f, 0.0, -0.3f),
			glm::vec3(1, 1, 1),
			glm::vec2(0.25, 0)));
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(0.3f, 0.0, 0.3f),
			glm::vec3(1, 1, 1),
			glm::vec2(0.25, 0.25)));
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(0.3f, 0.0, 0.3f),
			glm::vec3(1, 1, 1),
			glm::vec2(0.25, 0.25)));
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(-0.3f, 0.0, 0.3f),
			glm::vec3(1, 1, 1),
			glm::vec2(0, 0.25)));
	mesh.AddToVerticies(
		UncompressedVertex(glm::vec3(-0.3f, 0.0, -0.3f),
			glm::vec3(1, 1, 1),
			glm::vec2(0, 0))); 
	} //Belly//Belly //Belly

	//Back
	{ 
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.3f, 0.5, -0.3f),
				glm::vec3(1, 1, 1),
				glm::vec2(0, 0)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(0.3f, 0.5, -0.3f),
				glm::vec3(1, 1, 1),
				glm::vec2(0.25, 0)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(0.3f, 0.5, 0.3f),
				glm::vec3(1, 1, 1),
				glm::vec2(0.25, 0.25)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(0.3f, 0.5, 0.3f),
				glm::vec3(1, 1, 1),
				glm::vec2(0.25, 0.25)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.3f, 0.5, 0.3f),
				glm::vec3(1, 1, 1),
				glm::vec2(0, 0.25)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.3f, 0.5, -0.3f),
				glm::vec3(1, 1, 1),
				glm::vec2(0.0, 0.0)));
	}

	//Chin
	{
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.2f, 0.5, 0.3f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(0.2f, 0.5, 0.3f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.2f, 0.5, 0.5f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));

		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.2f, 0.5, 0.5f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(0.2f, 0.5, 0.5f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(0, 1)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.2f, 0.5, 0.3f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));

	}

	//Head Top
	{
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.2f, 0.7, 0.3f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(0.2f, 0.7, 0.3f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.2f, 0.7, 0.5f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));

		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.2f, 0.7, 0.5f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(0.2f, 0.7, 0.5f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));
		mesh.AddToVerticies(
			UncompressedVertex(glm::vec3(-0.2f, 0.7, 0.3f),
				glm::vec3(0.1f, 0.2f, 0.3f),
				glm::vec2(1, 0)));	}
	mesh.AddToElements(0);
	mesh.AddToElements(1);
	mesh.AddToElements(2);
	mesh.AddToElements(3);
	mesh.AddToElements(4);
	mesh.AddToElements(5);




	mesh.verticiesSetReady();
	FindTargetSpot();

}
void ProtoAnimal::Draw(Shader& shader)
{
	mesh.Draw(shader, Position, true);
}

void ProtoAnimal::Tick(float dt) 
{
	


	if (!reacherdTarget )
	{
		glm::vec3 dir = glm::normalize(TargetPos - Position);
		//if(!checkCollision(dir * speed * dt, world))
		velocity = dir * speed * dt;

		if (glm::distance(Position, TargetPos) < 1.f) reacherdTarget = true;

	}
	else
	{
		FindTargetSpot();
	}
	glm::vec3 Grav(0, -0.2, 0);

	bool isOnGround = checkCollision(Grav + Position, world);
	
	if (!isOnGround && velocity.y>-3) velocity += Grav;

	PrevPosition[1] = PrevPosition[0];
	PrevPosition[0] = Position;

	HandleCollisions(velocity);
	Position += velocity;
	velocity *= 0.3;
}

bool ProtoAnimal::HandleCollisions(glm::vec3& velocity)
{
	bool ret = false;
	if (CheckCollisionSide(glm::vec3(velocity.x, 0, 0)))
	{
		velocity.x = 0;
		ret = true;

	}
	if (CheckCollisionSide(glm::vec3(0, velocity.y, 0)))
	{
		velocity.y = 0;
		ret = true;
	}
	if (CheckCollisionSide(glm::vec3(0, 0, velocity.z)))
	{
		velocity.z = 0;
		ret = true;
	}

	return ret;
}

bool ProtoAnimal::CheckCollisionSide(glm::vec3 dir)
{
	return  checkCollision(Position + dir, world);
}

bool ProtoAnimal::comparePrevPositions()
{

	return abs(PrevPosition[0].x - PrevPosition[1].x) < 0.4f && glm::abs(PrevPosition[0].z - PrevPosition[1].z) < 0.4f;
 }

void ProtoAnimal::FindTargetSpot()
{
	int diffx = Util::GetInstance()->random(-5, 5);
	int diffz = Util::GetInstance()->random(-5, 5);
	int diffy = Util::GetInstance()->random(0, 0);

	glm::vec3 PosDif(diffx, diffy, diffz);
	Block* b = world->chunkMenager.GetBlockInWorld(PosDif + Position);
	if (b == nullptr || !Util::GetInstance()->BLOCKS[b->ID].Collidable)
	{
		b = world->chunkMenager.GetBlockInWorld(PosDif + Position + glm::vec3(0, -1, 0));
		if (b != nullptr && Util::GetInstance()->BLOCKS[b->ID].Collidable)
		{
			TargetPos = PosDif + glm::floor(Position);
			reacherdTarget = false;
		}
	}
}
