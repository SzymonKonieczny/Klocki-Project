#pragma once
#ifndef CHUNK_H
#define CHUNK_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>


#include "Block.h"
#include "ChunkMesh.h"
#include "GLOBAL.h"

#include "SimplexNoise.h"
class Chunk
{
	std::vector<Block> Blocks; //Vector of block IDs that make up teh chunk
	glm::ivec2 ChunkPos; // ChunkPos.y = Z coordinate in the world
	ChunkMesh mesh;
	std::unordered_map<glm::vec3, int> block_map;

	int column_heights[16][16];
public:
	Chunk(glm::vec2 ChunkCoords);
	void Generate(int height_);
	void UpdateMesh();
	void Draw(Shader& shader);
	bool setblock(glm::vec3 LocPos, int ID);

	void deleteblock(glm::vec3 LocPos);
	void setWorldBlock(glm::vec3 LocPos);
	bool isPositionViable(glm::vec3 LocPos);
	Block* vec3ToBlock(glm::vec3 LocPos);

};
#endif // !CHUNK_H