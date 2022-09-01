#pragma once

#ifndef CHUNKMENAGER_H
#define CHUNKMENAGER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>
struct Block;

class Chunk;
class ChunkMenager
{
public:
	static std::unordered_map<glm::vec2, std::vector<Block>> BlockQueuesMap;

	std::unordered_map<glm::vec2, Chunk> ChunkMap;
	void HandleWorldLoadingPositionChangeBased();
	void HandleWorldLoadingDistanceBased();
	void SetBlock(glm::vec3 WorldPos, Block block);
	void NewChunk(glm::vec2 ChunkPos);

};

#endif // !CHUNKMENAGER_H

