#pragma once
#include "ChunkMenager.h"
#include "Chunk.h"

#include <memory>
#include "SimplexNoise.h"
enum BIOMES {
	Forest,
	Desert,
	Mountain
};

class BaseBiome {
public:
	BaseBiome(std::string EncodedTree, ChunkMenager* _chunkmenager);
	ChunkMenager* chunkmenager;
	virtual BlockTypes GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock)=0;
	FastNoise::SmartNode<> NoiseFunc;
	virtual void GenerateFeatures(glm::vec3 pos)=0;

};
class BiomeForest : public BaseBiome
{
public:
	BlockTypes GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock);
	BiomeForest(ChunkMenager* _chunkmenager);
	void GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir = glm::vec3(0, 0, 1), int branches = 4);
	void GenerateFeatures(glm::vec3 pos);
};
class BiomeDesert : public BaseBiome
{
public:
	BlockTypes GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock);
	BiomeDesert(ChunkMenager* _chunkmenager);
	void GenerateCactus(glm::vec3 WorldPos);
	void GeneratePool(glm::vec3 WorldPos);

	void GenerateFeatures(glm::vec3 pos);
};
class BiomeMountain : public BaseBiome
{
public:
	BlockTypes GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock);
	BiomeMountain(ChunkMenager* _chunkmenager);

	void GenerateFeatures(glm::vec3 pos);
};


