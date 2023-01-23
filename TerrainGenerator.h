#pragma once

#include "BaseTerrainGenerator.h"
#include "Biome.h"
class TerrainGenerator : private BaseTerrainGenerator
{
	FastNoise::SmartNode<> fnGeneratorBiomeOracle;
	BiomeForest Forest;
	BiomeDesert Desert;
	BiomeMountain Mountain;


	struct NoiseMaps
	{
		std::vector<float> noiseOutputBiome(ChunkSize* ChunkSize);
		std::vector<float> noiseOutputDesert(ChunkSize* ChunkSize);
		std::vector<float> noiseOutputForest(ChunkSize* ChunkSize);
		std::vector<float> noiseOutputMountain(ChunkSize* ChunkSize);
	};
	void GenerateOnBiomeEdge(NoiseMaps& Noises,std::shared_ptr<Chunk> chunkptr);
	public:
	void Generate(std::shared_ptr<Chunk> chunkptr);
	BIOMES DecideBiome(float BiomeNoiseOutput);
	void GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir = glm::vec3(0, 0, 1), int branches = 4);
	void TryToGenerateHouse(glm::vec3 WorldPos);
	TerrainGenerator(ChunkMenager* menager);
	~TerrainGenerator();
};