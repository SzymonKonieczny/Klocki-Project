#pragma once

#ifndef CHUNKMENAGER_H
#define CHUNKMENAGER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>
#include <memory>

#include "Player.h"

struct Block;
class World;
class Chunk;
class ChunkMenager
{
	int FramesTillResetQueue = 800;
	std::mutex WorldMapMutex;
public:
	ChunkMenager(World* wrld);
	void SpawnChunks(glm::vec3 PlayerPos);
	std::unordered_map<glm::vec2, std::vector<Block>> BlockQueuesMap;
	World* world;

	std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> ChunkMap;

	void HandleWorldLoadingPositionChangeBased(Player& player);
	void HandleWorldLoadingDistanceBased();
	void SetBlockInWorld(glm::vec3 WorldPos, int ID);
	void SetBlockInWorld(glm::vec3 LocalPos, glm::vec2 ChunkPos, int ID);

	std::shared_ptr<Chunk> GetChunkAt(glm::vec2 ChunkPos);
	void EraseChunkAt(glm::vec2 ChunkPos);

	Block* GetBlockInWorld(glm::vec3 WorldPos);
	Block* GetBlockInWorld(glm::vec3 LocalPos, glm::vec2 ChunkPos);

	void NewChunk(glm::vec2 ChunkPos);

};

#endif // !CHUNKMENAGER_H

