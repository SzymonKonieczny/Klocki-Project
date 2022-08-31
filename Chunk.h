#pragma once
#ifndef CHUNK_H
#define CHUNK_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>

#include "BlockTypes.h"
#include "BlockTemplate.h"
#include "FaceBuilder.h"

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
	//std::vector<Block> QueuedBlocks;
	int column_heights[16][16];
public:
	Chunk(glm::vec2 ChunkCoords);
	void Generate(int height_);
	void UpdateMesh(); //clear the mesh, and rebuild
	void UpdateMeshOnlyAdd(std::vector<Block>& BlocksToAdd); //only add to the existing mesh
	void Draw(Shader& shader);
	bool setblock(glm::vec3 LocPos, int ID);
	void deleteblock(glm::vec3 LocPos);
	void setWorldBlock(glm::vec3 LocPos);
	bool isPositionViable(glm::vec3 LocPos);
	void UpdateBlocksFromBlockQueueMap(bool JustNewBlocks);
	Block* vec3ToBlock(glm::vec3 LocPos);
	~Chunk();


	static std::unordered_map<glm::vec2, std::vector<Block>> BlockQueuesMap;

};
#endif // !CHUNK_H