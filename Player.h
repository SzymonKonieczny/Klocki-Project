#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"
#include "Mesh.h"
#include "FaceBuilder.h"
class World;
class Player
{
	bool CheckCollisionSide(glm::vec3 Velocity);

	Mesh* Compass;
	float crntTime;
	float F3Cooldown=0;
	float RCooldown = 0;
	bool noClip = false;
	bool firstClick = true;
	bool isCompassOn = false;
	bool isOnGround;
	float speed = 0.01f;
	float sensitivity = 100.0f;
	float jumpForce = 10.f;
	Shader* UsedShader;
	glm::vec3 LookingAtDir = glm::vec3(0.0f, 0.0f, -1.0f);
public:
	glm::vec3 velocity;
	float drag = 0.2f;
	glm::vec2 LastFrameChunkPos;
	glm::vec3 Position = glm::vec3(0.0f, 70.0f, 2.0f);

	Camera Cam;

	World* world;
	Player();
	bool HandleCollisions(glm::vec3& Velocity);

	void Update(float dt);
	void SwitchCompassOnOff();
	void SetShader(Shader* shader);
	void HandleInput(float dt);
};

#endif // !PLAYER_H
