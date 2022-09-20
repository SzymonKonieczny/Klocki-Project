#pragma once
#include "ChunkMenager.h"
#include "Chunk.h"

#include <memory>
#include "SimplexNoise.h"
enum BIOMES {
	Forest,
	Desert
};

class BaseBiome {
public:
	BaseBiome(std::string EncodedTree);

	virtual BlockTypes GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock)=0;
	FastNoise::SmartNode<> NoiseFunc;
	virtual void GenerateFeatures()=0;

};
class BiomeForest : public BaseBiome
{
public:
	BlockTypes GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock);
	BiomeForest();
	void GenerateFeatures();
};
class BiomeDesert : public BaseBiome
{
public:
	BlockTypes GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock);
	BiomeDesert();
	void GenerateFeatures();
};

