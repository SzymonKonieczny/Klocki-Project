#pragma once

#ifndef CHUNKMENAGER_H
#define CHUNKMENAGER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>
#include "Player.h"
struct Block;
class World;
class Chunk;
class ChunkMenager
{
	int FramesTillResetQueue = 800;
public:
	ChunkMenager(World* wrld);

	std::unordered_map<glm::vec2, std::vector<Block>> BlockQueuesMap;
	World* world;
	std::unordered_map<glm::vec2, Chunk> ChunkMap;
	void HandleWorldLoadingPositionChangeBased(Player& player);
	void HandleWorldLoadingDistanceBased();
	void SetBlockInWorld(glm::vec3 WorldPos, Block block);
	void NewChunk(glm::vec2 ChunkPos);

};

#endif // !CHUNKMENAGER_H
