#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"

class Player
{

	bool firstClick = true;
	float speed = 0.1f;
	float sensitivity = 100.0f;
	Shader* UsedShader;
	glm::vec3 LookingAtDir = glm::vec3(0.0f, 0.0f, -1.0f);
public:
	glm::vec2 LastFrameChunkPos;
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 2.0f);

	Camera Cam;
	Player();
	void Update();
	void SetShader(Shader* shader);
	void HandleInput();
};

#endif // !PLAYER_H
