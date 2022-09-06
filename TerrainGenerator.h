#pragma once
#include "BaseTerrainGenerator.h"

class TerrainGenerator : private BaseTerrainGenerator
{

	public:
	void Generate(std::shared_ptr<Chunk> chunkptr);
	void GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir = glm::vec3(0, 0, 1), int branches = 6);

	TerrainGenerator(ChunkMenager* menager);
	~TerrainGenerator();
};