#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"
#include "CompassMesh.h"
#include "ChunkMesh.h"
#include "FaceBuilder.h"
#include "Collider.h"
#include "Ray.h"
class World;
//class CompassMesh;
//class ChunkMesh;

class Player
{
	bool CheckCollisionSide(glm::vec3 Velocity);
	RayInfo Rayinfo;
	Collider collider;
	CompassMesh* Compass;
	ChunkMesh* BlockSelect;
	bool isBlockSelectMade = false;
	float crntTime;
	float F3Cooldown=0;
	float RCooldown = 0;
	bool noClip = true;
	bool firstClick = true;
	bool isCompassOn = false;
	bool isOnGround;
	float speed = 2.5f;
	float sensitivity = 100.0f;
	float jumpForce = 0.2f;
	float BLocksCooldown = 0.1;
	Shader* UsedBlockShader;
	Shader* UsedEntityShader;
	glm::vec3 LookingAtDir = glm::vec3(0.0f, 0.0f, -1.0f);
	bool MarkedFirst = false; //for line generating
	glm::vec3 FirstSel;
public:
	glm::vec3 velocity;
	float drag = 0.2f;
	glm::vec2 LastFrameChunkPos;
	glm::vec3 Position = glm::vec3(1000.0f, 70.0f, 1000.0f);

	Camera Cam;

	World* world;
	Player();
	bool HandleCollisions(glm::vec3& Velocity);

	void Update(float dt);
	void SwitchCompassOnOff();
	void SetShader(Shader* BlockShader, Shader* EntityShader);
	void HandleInput(float dt);
};

#endif // !PLAYER_H
