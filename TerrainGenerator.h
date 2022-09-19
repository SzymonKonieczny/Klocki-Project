#pragma once
#include "BaseTerrainGenerator.h"

class TerrainGenerator : private BaseTerrainGenerator
{
	FastNoise::SmartNode<> fnGeneratorBiomeOracle;
	FastNoise::SmartNode<> Desert;
	FastNoise::SmartNode<> Hills;
	FastNoise::SmartNode<> Ocean;



	
	public:
	void Generate(std::shared_ptr<Chunk> chunkptr);
	void GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir = glm::vec3(0, 0, 1), int branches = 4);
	void TryToGenerateHouse(glm::vec3 WorldPos);
	TerrainGenerator(ChunkMenager* menager);
	~TerrainGenerator();
};