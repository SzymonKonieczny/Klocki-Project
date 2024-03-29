#include "Player.h"
#include "World.h"
#include "Ray.h"
/*glm::vec3(0.0f, 0.0, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0, 1)*/
Player::Player(): Cam(Position), collider(glm::vec3(-0.25,-1.8,-0.25), glm::vec3(0.25, 0, 0.25))
{
	
}
bool Player::CheckCollisionSide(glm::vec3 dir)
{
	bool ret = collider.checkCollision(Position + dir,world);

	// VVVVV POINT COLLISION VVVVV
	/*auto chunk = world->chunkMenager.ChunkMap.find(Util::WorldPosToChunkPos(Position + dir));
	if (chunk != world->chunkMenager.ChunkMap.end())
	{	
		if (!chunk->second->generated) return ret;
		glm::vec3 locpos = Util::WorldPosToLocalPos(Position+dir);
		Block* b = chunk->second->vec3ToBlock(locpos);
		if (b != nullptr )
			if(Util::GetInstance()->BLOCKS[b->ID].Collidable)	ret = true;

	}*/

	return ret;
}
bool Player::HandleCollisions(glm::vec3& Velocity) // returns if the position collides
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

void Player::Update(float dt)
{
	if (!isBlockSelectMade) { //very dirty, very temporary
		BlockSelect = new ChunkMesh();
		FaceBuilder::BuildFace(*BlockSelect, Faces::Up, glm::vec3(0, 0, 0), BlockTypes::Cactus, BlockShapes::BlockShape);
		isBlockSelectMade = true;
		BlockSelect->verticiesSetReady();
	}

	Rayinfo = Ray::Cast(Position, LookingAtDir, world, 4);

	if (!Rayinfo.Miss)BlockSelect->Draw(*UsedBlockShader, Rayinfo.HitPos, true);
	isOnGround = CheckCollisionSide(glm::vec3(0, -0.2, 0));

	HandleInput(dt);
	//temporary gravity
	if (!noClip) velocity.y -= 0.8f * dt;
	if(!noClip)HandleCollisions(velocity);

	Position += velocity;
	velocity.x *=  drag*dt;//glm::vec3(drag*dt);
	velocity.z *= drag * dt;
	if (noClip) velocity.y *= drag * dt;

	Cam.UpdateView();
	//Cam.UpdateUniformsTransparent();

	Cam.Position = Position;
	//Cam.Position.y += 2;
	Cam.LookingAtDir = LookingAtDir;

	
	if (isCompassOn)
	{
		UsedEntityShader->Activate();
		Cam.UpdateUniformsEntity();
		Compass->Draw(*UsedEntityShader,Position+(LookingAtDir),true);

	}
	

} 

void Player::SwitchCompassOnOff()
{
	if (Compass == nullptr)
	{
		Compass = new CompassMesh();
		
		Compass->GetVertexVector().push_back(
			UncompressedVertex(glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(1, 0.99)));
		Compass->GetVertexVector().push_back(
			UncompressedVertex(glm::vec3(0.0, 0.1, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(0.99, 1)));
		Compass->GetVertexVector().push_back(
			UncompressedVertex(glm::vec3(0.3, 0, 0.0f),
				glm::vec3(0.6f, 0.0f, 0.0f),
				glm::vec2(1, 1)));
		



		Compass->GetVertexVector().push_back(
			UncompressedVertex(glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(1, 0.99)));
		Compass->GetVertexVector().push_back(
			UncompressedVertex(glm::vec3(0.0, 0.3, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(0.99, 1)));
		Compass->GetVertexVector().push_back(
			UncompressedVertex(glm::vec3(0.1, 0, 0.0f),
				glm::vec3(0.0f, 0.6f, 0.0f),
				glm::vec2(1, 1)));



		Compass->GetVertexVector().push_back(
			UncompressedVertex(glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(1, 0.99)));
		Compass->GetVertexVector().push_back(
			UncompressedVertex(glm::vec3(0.0, 0.1, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(0.99, 1)));
		Compass->GetVertexVector().push_back(
			UncompressedVertex(glm::vec3(0.0, 0, 0.3f),
				glm::vec3(0.0f, 0.0f, 0.6f),
				glm::vec2(1, 1)));
		
		Compass->verticiesSetReady();
	}
	isCompassOn = !isCompassOn;
}

void Player::SetShader(Shader* BlockShader, Shader* EntityShader)
{
	UsedBlockShader = BlockShader;
	UsedEntityShader = EntityShader;
}

void Player::HandleInput(float dt)
{
	crntTime = glfwGetTime();
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_C) == GLFW_PRESS)
	{
		if (crntTime - F3Cooldown > 0.5f)
		{
			F3Cooldown = glfwGetTime();
			noClip = !noClip;
		}


	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_P) == GLFW_PRESS)
	{
		if (crntTime - RCooldown > 0.5f)
		{
			glm::vec2 res2 = Util::WorldPosToChunkPos(Position);
			glm::vec3 res = Util::WorldPosToLocalPos(Position);
			std::cout << " Player at Chunk Pos " << res2.x << ':' << res2.y << std::endl;
			std::cout << " Player at Local Pos " << res.x << ':' << res.z << std::endl;
			std::cout << " Player at World Pos " << Position.x << ':' << Position.y << ':' << Position.z << std::endl;

			RCooldown = glfwGetTime();
		}


	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_R) == GLFW_PRESS)
	{
		if (crntTime - RCooldown > 0.5f)
		{
			glm::vec2 res2 = Util::WorldPosToChunkPos(Position);
			world->AddChunksMeshToUpdate(res2);
			RCooldown = glfwGetTime();

			std::cout << "q12 = " << world->chunkMenager.GetChunkAt(res2)->q12;
			std::cout << " q22 = " << world->chunkMenager.GetChunkAt(res2)->q22 << std::endl;
			std::cout << "q11 = " << world->chunkMenager.GetChunkAt(res2)->q11;
			std::cout << " q21 = " << world->chunkMenager.GetChunkAt(res2)->q21 << std::endl;
			

		}


	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_U) == GLFW_PRESS)
	{
		if (crntTime - RCooldown > 0.5f)
		{
			if (MarkedFirst	)
			{

					glm::vec3 blockPos;
				for (int i = 1; i < (int)glm::distance(FirstSel, Position);i++)
				{

					blockPos = glm::vec3(Util::LinearInterpolation(FirstSel.x, Position.x, i / glm::abs(Position.x - FirstSel.x)),
						Util::LinearInterpolation(FirstSel.y, Position.y,  (i/ glm::abs(Position.y - FirstSel.y)))
						, Util::LinearInterpolation(FirstSel.z, Position.z, i / glm::abs(Position.z - FirstSel.z)));
					world->chunkMenager.SetBlockInWorld(blockPos, BlockTypes::Cobble);
					std::cout << " block at  " << blockPos.x << ':' << blockPos.y << ':' << blockPos.z << std::endl;
				}

				MarkedFirst = false;
			}
			else {
				MarkedFirst = true;
				FirstSel = Position;
			}

		}


	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_B) == GLFW_PRESS)
	{
 		std::cout << "breaking..." << std::endl;

	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_O) == GLFW_PRESS)
	{
		if (crntTime - F3Cooldown > 0.5f)
		{
				SwitchCompassOnOff();
				F3Cooldown = glfwGetTime();
		}
	}

	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_K) == GLFW_PRESS)
	{
		if (crntTime - F3Cooldown > 0.5f)
		{
			
			world->entityMenager.SpawnEntity(Position- glm::vec3(0,1,0), EntityTypes::Proto);
			F3Cooldown = glfwGetTime();

		}
	}

	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		velocity += dt * speed * glm::normalize( glm::vec3(LookingAtDir.x, 0, LookingAtDir.z));
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		velocity += dt * speed * -glm::normalize(glm::cross(glm::vec3(LookingAtDir.x, 0, LookingAtDir.z), glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		velocity += dt * speed * -glm::normalize(glm::vec3(LookingAtDir.x, 0, LookingAtDir.z));
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		velocity += dt* speed * glm::normalize(glm::cross(glm::vec3(LookingAtDir.x,0, LookingAtDir.z), glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (!noClip && isOnGround)
		{
			velocity = jumpForce * glm::vec3(0.0f, 1.0f, 0.0f);
		}
		else if (noClip) velocity += speed * dt * glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		velocity += dt * speed * glm::vec3(0.0f, -1.0f, 0.0f);
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetCursorPos(Window::GetInstance()->window, (Window::GetInstance()->WinHeight / 2), (Window::GetInstance()->WinWidth / 2));
		firstClick = true;
		glfwSetInputMode(Window::GetInstance()->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		speed = 20.f;
	}
	else if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		speed = 3.5f;
	}

	if (firstClick && glfwGetMouseButton(Window::GetInstance()->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetCursorPos(Window::GetInstance()->window, (Window::GetInstance()->WinHeight / 2), (Window::GetInstance()->WinWidth / 2));
		firstClick = false;
		glfwSetInputMode(Window::GetInstance()->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else
	{
		if (!firstClick && !Rayinfo.Miss && (crntTime - BLocksCooldown) > 0.2f && glfwGetMouseButton(Window::GetInstance()->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			world->chunkMenager.SetBlockInWorld(Rayinfo.HitPos, BlockTypes::Air);
			BLocksCooldown = glfwGetTime();

		}
		if (!firstClick && !Rayinfo.Miss && (crntTime - BLocksCooldown) > 0.2f && glfwGetMouseButton(Window::GetInstance()->window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			world->chunkMenager.SetBlockInWorld(Rayinfo.HitFromPos, BlockTypes::Cobble);
			BLocksCooldown = glfwGetTime();

		}
	}


	



	if (!firstClick)
	{
		double mouseX;
		double mouseY;

		glfwGetCursorPos(Window::GetInstance()->window, &mouseX, &mouseY);


		float rotX = sensitivity * (float)(mouseY - (Window::GetInstance()->WinHeight / 2)) / Window::GetInstance()->WinHeight;
		float rotY = sensitivity * (float)(mouseX - (Window::GetInstance()->WinWidth / 2)) / Window::GetInstance()->WinWidth;

		glm::vec3 newOrientation = glm::rotate(LookingAtDir, glm::radians(-rotX), glm::normalize(glm::cross(LookingAtDir, glm::vec3(0.0f, 1.0f, 0.0f))));

		if (abs(glm::angle(newOrientation, glm::vec3(0.0f, 1.0f, 0.0f)) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			LookingAtDir = newOrientation;
		}


		LookingAtDir = glm::rotate(LookingAtDir, glm::radians(-rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		glfwSetCursorPos(Window::GetInstance()->window, (Window::GetInstance()->WinWidth / 2), (Window::GetInstance()->WinHeight / 2));
	
	}
}