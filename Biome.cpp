#include "Biome.h"
BaseBiome::BaseBiome(std::string EncodedTree)
{
	NoiseFunc = FastNoise::NewFromEncodedNodeTree(EncodedTree.c_str());
}



BlockTypes BiomeForest::GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock)
{
	if (isSurfaceBlock) return BlockTypes::Grass;
	else return BlockTypes::Stone;
}

BiomeForest::BiomeForest() : BaseBiome("DQACAAAAzczMPQ0AAgAAAI/CNUAIAAAUrjdBADMzMz8Aj8KBQQBSuB7A")
{

}

void BiomeForest::GenerateFeatures()
{

}

BlockTypes BiomeDesert::GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock)
{
	if (isSurfaceBlock) return BlockTypes::Sand;
	else return BlockTypes::Stone;
}

BiomeDesert::BiomeDesert(): BaseBiome("EwAK16M+DQACAAAAw/UoPw0ABAAAAAAAAEAJAAAAAIA/AAAAAD8AAACAPwAAAAAA")
{
}

void BiomeDesert::GenerateFeatures()
{
}
