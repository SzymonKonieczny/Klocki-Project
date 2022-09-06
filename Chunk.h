#pragma once
#ifndef CHUNK_H
#define CHUNK_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>
#include <thread>
#include <mutex>

#include "BlockTypes.h"
#include "BlockTemplate.h"
#include "FaceBuilder.h"

#include "Block.h"
#include "ChunkMesh.h"
#include "GLOBAL.h"
#include "SimplexNoise.h"


#include "ChunkMenager.h"

class ChunkMenager;


class Chunk
{
	std::mutex VertexMutex;
	std::vector<Block> Blocks; //Vector of block IDs that make up teh chunk
	std::mutex BlocksMutex;
public:

	bool generated = false;
	bool meshed = false;
	ChunkMenager* chunkMenager;

	glm::vec2 ChunkPos; // ChunkPos.y = Z coordinate in the world
	ChunkMesh mesh;
	std::unordered_map<glm::vec3, int> block_map;

	int column_heights[16][16];
	bool mutexMakeshift=true;



	bool isDirty = false;
	Chunk(glm::vec2 ChunkCoords, ChunkMenager* ChunkMenager_);
	void Generate(int height_);
	void UpdateMesh(); //clear the mesh, and rebuild
	bool CheckIfSolidBlock(glm::vec3 Pos);
	void UpdateMeshOnlyAdd(std::vector<Block>& BlocksToAdd); //only add to the existing mesh
	void Draw(Shader& shader);
	bool setblock(glm::vec3 LocPos, int ID);
	void deleteblock(glm::vec3 LocPos);
	void setWorldBlock(glm::vec3 LocPos);
	void UpdateMeshOnlyAddSingleBlock(Block block);
	void GenerateTree(glm::vec3 LocPos, glm::vec3 Dir = glm::vec3(0, 0, 1), int branches = 2);
	bool isPositionViable(glm::vec3 LocPos);
	void UpdateBlocksFromBlockQueueMap(bool JustNewBlocks);
	Block* vec3ToBlock(glm::vec3 LocPos);
	void LockBlockMutex();
	void UnlockBlockMutex();

	~Chunk();



};
#endif // !CHUNK_H