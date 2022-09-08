#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"
#include "Mesh.h"
#include "FaceBuilder.h"
class World;
class Player
{

	Mesh* Compass;
	float crntTime;
	float F3Cooldown=0;
	bool firstClick = true;
	bool isCompassOn = false;
	float speed = 0.1f;
	float sensitivity = 100.0f;
	Shader* UsedShader;
	glm::vec3 LookingAtDir = glm::vec3(0.0f, 0.0f, -1.0f);
public:
	glm::vec2 LastFrameChunkPos;
	glm::vec3 Position = glm::vec3(0.0f, 70.0f, 2.0f);

	Camera Cam;


	World* world;
	Player();
	void Update(float dt);
	void SwitchCompassOnOff();
	void SetShader(Shader* shader);
	void HandleInput(float dt);
};

#endif // !PLAYER_H
