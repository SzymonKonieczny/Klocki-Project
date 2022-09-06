#include "Player.h"
#include "World.h"
/*glm::vec3(0.0f, 0.0, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0, 1)*/
Player::Player(): Cam(Position)
{

}

void Player::Update(float dt)
{

	HandleInput(dt);

	Cam.UpdateView(*UsedShader);
	Cam.Position = Position;
	Cam.LookingAtDir = LookingAtDir;

	if (isCompassOn)
	{
		
		Compass->Draw(*UsedShader,Position+(LookingAtDir),true);

	}
	

}

void Player::SwitchCompassOnOff()
{
	if (Compass == nullptr)
	{
		Compass = new Mesh();
		
		Compass->GetVertexVector().push_back(
			Vertex(glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(1, 0.99)));
		Compass->GetVertexVector().push_back(
			Vertex(glm::vec3(0.0, 0.1, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(0.99, 1)));
		Compass->GetVertexVector().push_back(
			Vertex(glm::vec3(0.3, 0, 0.0f),
				glm::vec3(0.6f, 0.0f, 0.0f),
				glm::vec2(1, 1)));




		Compass->GetVertexVector().push_back(
			Vertex(glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(1, 0.99)));
		Compass->GetVertexVector().push_back(
			Vertex(glm::vec3(0.0, 0.3, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(0.99, 1)));
		Compass->GetVertexVector().push_back(
			Vertex(glm::vec3(0.1, 0, 0.0f),
				glm::vec3(0.0f, 0.6f, 0.0f),
				glm::vec2(1, 1)));



		Compass->GetVertexVector().push_back(
			Vertex(glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(1, 0.99)));
		Compass->GetVertexVector().push_back(
			Vertex(glm::vec3(0.0, 0.1, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(0.99, 1)));
		Compass->GetVertexVector().push_back(
			Vertex(glm::vec3(0.0, 0, 0.3f),
				glm::vec3(0.0f, 0.0f, 0.6f),
				glm::vec2(1, 1)));


	}
	isCompassOn = !isCompassOn;
}

void Player::SetShader(Shader* shader)
{
	UsedShader = shader;
}

void Player::HandleInput(float dt)
{
	crntTime = glfwGetTime();

	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_P) == GLFW_PRESS)
	{
		glm::vec2 res2 = Util::WorldPosToChunkPos(Position);

		std::cout << " Player at Chunk Pos " << res2.x << ':' << res2.y << std::endl;
		std::cout << " Player at World Pos " << Position.x << ':' << Position.y << ':' << Position.z << std::endl;

	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_R) == GLFW_PRESS)
	{
		glm::vec2 res2 = Util::WorldPosToChunkPos(Position);
		world->AddChunksMeshToUpdate(res2);

	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_B) == GLFW_PRESS)
	{
		std::cout << "breaking..." << std::endl;

	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_F3) == GLFW_PRESS)
	{
		if (crntTime - F3Cooldown > 0.5f)
		{
				SwitchCompassOnOff();
				F3Cooldown = glfwGetTime();
		}
	

	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += dt * speed * glm::normalize( glm::vec3(LookingAtDir.x, 0, LookingAtDir.z));
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += dt * speed * -glm::normalize(glm::cross(glm::vec3(LookingAtDir.x, 0, LookingAtDir.z), glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += dt * speed * -glm::normalize(glm::vec3(LookingAtDir.x, 0, LookingAtDir.z));
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += dt* speed * glm::normalize(glm::cross(glm::vec3(LookingAtDir.x,0, LookingAtDir.z), glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += dt * speed * glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		Position += dt * speed * glm::vec3(0.0f, -1.0f, 0.0f);
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetCursorPos(Window::GetInstance()->window, (Window::GetInstance()->WinHeight / 2), (Window::GetInstance()->WinWidth / 2));
		firstClick = true;
		glfwSetInputMode(Window::GetInstance()->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		speed = 100.f;
	}
	else if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		speed = 10.f;
	}

	if (firstClick && glfwGetMouseButton(Window::GetInstance()->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetCursorPos(Window::GetInstance()->window, (Window::GetInstance()->WinHeight / 2), (Window::GetInstance()->WinWidth / 2));
		firstClick = false;
		glfwSetInputMode(Window::GetInstance()->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
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