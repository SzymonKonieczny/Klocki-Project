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
		std::vector<float> noiseOutputBiome;
		std::vector<float> noiseOutputDesert;
		std::vector<float> noiseOutputForest;
		std::vector<float> noiseOutputMountain;
	};

	bool isInOneBiome(NoiseMaps& maps);
	void GenerateNormally(NoiseMaps& Noises, std::shared_ptr<Chunk> chunkptr);
	void GenerateOnBiomeEdge(NoiseMaps& Noises,std::shared_ptr<Chunk> chunkptr);
	public:
	void Generate(std::shared_ptr<Chunk> chunkptr);
	BIOMES DecideBiome(float BiomeNoiseOutput);
	void GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir = glm::vec3(0, 0, 1), int branches = 4);
	void TryToGenerateHouse(glm::vec3 WorldPos);
	TerrainGenerator(ChunkMenager* menager);
	~TerrainGenerator();
};