#include "Player.h"

Player::Player(): Cam(Position)
{


}

void Player::Update()
{
	HandleInput();
	Cam.UpdateView(*UsedShader);
	Cam.Position = Position;
	Cam.LookingAtDir = LookingAtDir;
}

void Player::SetShader(Shader* shader)
{
	UsedShader = shader;
}

void Player::HandleInput()
{

	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * LookingAtDir;
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(LookingAtDir, glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -LookingAtDir;
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(LookingAtDir, glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		Position += speed * glm::vec3(0.0f, -1.0f, 0.0f);
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window::GetInstance()->window, 1);
	}
	if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(Window::GetInstance()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}

	if (firstClick)
	{
		glfwSetCursorPos(Window::GetInstance()->window, (Window::GetInstance()->WinHeight / 2), (Window::GetInstance()->WinWidth / 2));
		firstClick = false;
	}


	double mouseX;
	double mouseY;

	glfwGetCursorPos(Window::GetInstance()->window, &mouseX, &mouseY);


	float rotX = sensitivity * (float)(mouseY - (Window::GetInstance()->WinHeight / 2)) / Window::GetInstance()->WinHeight;
	float rotY = sensitivity * (float)(mouseX - (Window::GetInstance()->WinWidth / 2)) / Window::GetInstance()->WinWidth;

	glm::vec3 newOrientation = glm::rotate(LookingAtDir, glm::radians(-rotX), glm::normalize(glm::cross(LookingAtDir, glm::vec3(0.0f,1.0f,0.0f))));

	if (abs(glm::angle(newOrientation, glm::vec3(0.0f, 1.0f, 0.0f)) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		LookingAtDir = newOrientation;
	}

	LookingAtDir = glm::rotate(LookingAtDir, glm::radians(-rotY), glm::vec3(0.0f, 1.0f, 0.0f));

	glfwSetCursorPos(Window::GetInstance()->window, (Window::GetInstance()->WinWidth / 2), (Window::GetInstance()->WinHeight / 2));
}