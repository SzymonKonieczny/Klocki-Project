#include "Biome.h"
BaseBiome::BaseBiome(std::string EncodedTree, ChunkMenager* _chunkmenager)
{
	chunkmenager = _chunkmenager;
	NoiseFunc = FastNoise::NewFromEncodedNodeTree(EncodedTree.c_str());
}



BlockTypes BiomeForest::GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock)
{
	if (isSurfaceBlock) return BlockTypes::Grass;
	else return BlockTypes::Stone;
}

BiomeForest::BiomeForest(ChunkMenager* _chunkmenager) : BaseBiome("DQACAAAAzczMPQ0AAgAAAI/CNUAIAAAUrjdBADMzMz8Aj8KBQQBSuB7A",_chunkmenager)
{

}

void BiomeForest::GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir, int branches)
{
	if (Util::GetInstance()->random(1, 10) > 7 || branches <= 0)return;
	//glm::vec3 WorldPos = Util::LocPosAndChunkPosToWorldPos(LocPos,ChunkPos);
	glm::vec3 Up(0, 1, 0);
	chunkmenager->SetBlockInWorld(WorldPos, BlockTypes::Log);
	for (int i = 0; i < 3; i++)
	{
		WorldPos += Up;
		chunkmenager->SetBlockInWorld(WorldPos, BlockTypes::Log);


	}
	GenerateTree(WorldPos, glm::vec3(Util::GetInstance()->random(-1, 1), 0, Util::GetInstance()->random(-1, 1)), branches - 2);
	int rand = Util::GetInstance()->random(1, 3);
	for (int i = 0; i < rand; i++)
	{
		GenerateTree(WorldPos, glm::vec3(Util::GetInstance()->random(-1, 1), 0, Util::GetInstance()->random(-1, 1)), branches - 1);
	}
	for (int i = 0; i < 4; i++)
	{
		WorldPos += Up + Dir;
		//glm::vec3 WorldPos = Util::LocPosAndChunkPosToWorldPos(LocPos, ChunkPos);

		chunkmenager->SetBlockInWorld(WorldPos, BlockTypes::Leaves);

		chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(1, 0, 0), BlockTypes::Leaves);
		chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(0, 0, 1), BlockTypes::Leaves);
		chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(-1, 0, 0), BlockTypes::Leaves);
		chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(0, 0, -1), BlockTypes::Leaves);
	}
	GenerateTree(WorldPos, glm::vec3(Util::GetInstance()->random(-1, 1), 0, Util::GetInstance()->random(-1, 1)), branches - 1);
	rand = Util::GetInstance()->random(1, 3);
	for (int i = 0; i < rand; i++)
	{
		GenerateTree(WorldPos, glm::vec3(Util::GetInstance()->random(-1, 1), 0, Util::GetInstance()->random(-1, 1)), branches - 2);
	}



}

void BiomeForest::GenerateFeatures(glm::vec3 pos)
{
	if(Util::GetInstance()->random(0,1000)<5)
		GenerateTree(pos);
	



}

BlockTypes BiomeDesert::GetBlockTypeAt(glm::vec3 pos, bool isSurfaceBlock)
{
	if (isSurfaceBlock) return BlockTypes::Sand;
	else return BlockTypes::Stone;
}

BiomeDesert::BiomeDesert(ChunkMenager* _chunkmenager): BaseBiome("EwAK16M+DQACAAAAw/UoPw0ABAAAAAAAAEAJAAAAAIA/AAAAAD8AAACAPwAAAAAA", _chunkmenager )
{
}

void BiomeDesert::GenerateCactus(glm::vec3 WorldPos)
{
	chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(0, 1, 0), BlockTypes::Cactus);
	chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(0, 2, 0), BlockTypes::Cactus);
	chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(0, 3, 0), BlockTypes::Cactus);

}

void BiomeDesert::GeneratePool(glm::vec3 WorldPos)
{
	chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(0, -1, 0), BlockTypes::Water);
	chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(1, -1, 0), BlockTypes::Water);
	chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(0, -1, 1), BlockTypes::Water);
	chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(-1,-1, 0), BlockTypes::Water);
	chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(0, -1, -1),BlockTypes::Water);

}

void BiomeDesert::GenerateFeatures(glm::vec3 pos)
{
	if (Util::GetInstance()->random(0, 400) < 1)	GeneratePool(pos);
	else if (Util::GetInstance()->random(0, 100) < 1)
		GenerateCactus(pos);
}
