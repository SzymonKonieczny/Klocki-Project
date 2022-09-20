#pragma once
#include "ChunkMenager.h"
#include "Chunk.h"

#include <memory>
#include "SimplexNoise.h"

class BaseBiome {
public:
	BaseBiome(std::string EncodedTree);
	//BlockTypes SurfaceBlock = BlockTypes::Log;
	//BlockTypes UnderGround = BlockTypes::Log;

	virtual BlockTypes GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock)=0;
	FastNoise::SmartNode<> NoiseFunc;
	virtual void GenerateFeatures()=0;

};
class BiomeForest : public BaseBiome
{
public:
	//BlockTypes SurfaceBlock = BlockTypes::Grass;
	//BlockTypes UnderGround = BlockTypes::Stone;
	BlockTypes GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock);
	BiomeForest();
	void GenerateFeatures();
};
