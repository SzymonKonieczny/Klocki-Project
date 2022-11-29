#include "ProtoAnimal.h"
#include "World.h"
ProtoAnimal::ProtoAnimal(unsigned int ID, World* wrld, glm::vec3 Pos) :
	Collider(glm::vec3(-0.25, 0, -0.25),	glm::vec3(0.25, 0.9, 0.25)), Entity( Pos, wrld), id(ID)
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
	mesh.verticiesSetReady();

}
void ProtoAnimal::Draw(Shader& shader)
{
	mesh.Draw(shader, Position, true);
}

void ProtoAnimal::Tick(float dt) 
{
	


	if (!reacherdTarget && !comparePrevPositions())
	{
		glm::vec3 dir = glm::normalize(TargetPos - Position);
		//if(!checkCollision(dir * speed * dt, world))
		velocity = dir * speed * dt;

		if (glm::distance(Position, TargetPos) < 1.f) reacherdTarget = true;

	}
	else
	{
		int diffx = Util::GetInstance()->random(2,5);
		int diffz = Util::GetInstance()->random(2, 5);
		int diffy = Util::GetInstance()->random(-2, 1);

		glm::vec3 PosDif(diffx, diffy, diffz);
		Block* b = world->chunkMenager.GetBlockInWorld(PosDif + Position);
		if (b != nullptr && !Util::GetInstance()->BLOCKS[b->ID].Collidable)
		{
			b = world->chunkMenager.GetBlockInWorld(PosDif + Position + glm::vec3(0,-1,0));
			if (b != nullptr && Util::GetInstance()->BLOCKS[b->ID].Collidable)
			{
				TargetPos = PosDif + Position;
				reacherdTarget = false;
			}
		}

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

bool ProtoAnimal::HandleCollisions(glm::vec3& Velocity)
{
	bool ret = false;
	if (CheckCollisionSide(glm::vec3(Velocity.x, 0, 0)))
	{
		velocity.x = 0;
		ret = true;

	}
	if (CheckCollisionSide(glm::vec3(0, Velocity.y, 0)))
	{
		velocity.y = 0;
		ret = true;
	}
	if (CheckCollisionSide(glm::vec3(0, 0, Velocity.z)))
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
