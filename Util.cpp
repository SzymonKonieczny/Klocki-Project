#include "Util.h"
Util* Util::Instance = nullptr;

Util* Util::GetInstance()
{
	if (Instance == nullptr) Instance = new Util;

	return Instance;
}
float Util::random(int min, int max)
{

	std::uniform_int_distribution<> dist(min,max);
	return dist(gen);
	//return gen() % (max - min) + min;
}
Util::Util():gen(rd())
{

}



glm::vec2 Util::WorldPosToChunkPos(glm::vec3 WorldPos)
{

	//return glm::vec2(int(WorldPos.x/ChunkSize),int(WorldPos.z / ChunkSize));


	return glm::vec2(
		static_cast<int>(WorldPos.x < 0 ? ((WorldPos.x - ChunkSize) / ChunkSize) : (WorldPos.x / ChunkSize)),
		static_cast<int>(WorldPos.z < 0 ? ((WorldPos.z - ChunkSize) / ChunkSize) : (WorldPos.z / ChunkSize))
	);


}

glm::vec3 Util::LocPosAndChunkPosToWorldPos(glm::vec3 LocPos, glm::vec2 ChunkPos)
{

	return glm::vec3(LocPos.x + ChunkPos.x * ChunkSize, LocPos.y, LocPos.z + ChunkPos.y /*<- because chunkPos is a vec2*/ * ChunkSize);

}

glm::vec3 Util::WorldPosToLocalPos(glm::vec3 WorldPos)
{

	int x = static_cast<int>(WorldPos.x);

	int z = static_cast<int>(WorldPos.z);

	if (x < 0) x--;
	if (z < 0) z--; // 0 coordinate is in the positives, so negatives start at -1, chence chunkPos X =-1 are blocks -1 to -16, not 0 to 15

	return glm::vec3( (ChunkSize+(x%ChunkSize))%ChunkSize , glm::floor(WorldPos.y), (ChunkSize + (z % ChunkSize)) % ChunkSize); //hopson?

}

float Util::lerp(float v0, float v1, float t)
{
	return (1 - t) * v0 + t * v1;
}


void Util::LoadBlocks()
{


	int loadedAmout = 0;
	for (int i = 0; i < 5; i++) // 5 x 5 slots in the current atlas
	{
		if (loadedAmout >= amoutOfBlocks) break;
		for (int k = 0; k < 5; k++)
		{
			glm::vec2 testingX = glm::vec2(texturedimention * k, texturedimention * k + texturedimention);
			glm::vec2 testingY = glm::vec2(texturedimention * i, texturedimention * i + texturedimention);

			BLOCKS.push_back(BlockTemplate({ testingX,testingY ,true,true , "Unnamed", BlockTypes::Air }));
			loadedAmout++;
			if (loadedAmout >= amoutOfBlocks) break;
		}
	}
	//Here load properties of every block.
	BLOCKS[BlockTypes::Air].Collidable = false;
	BLOCKS[BlockTypes::Water].Collidable = false;
	BLOCKS[BlockTypes::Water].Solid = false;
	BLOCKS[BlockTypes::Leaves].Solid = false;


	BLOCKS[BlockTypes::Grass].name = "Grass Block";
	BLOCKS[BlockTypes::ShubiumOre].name = "Shubium Ore";
	BLOCKS[BlockTypes::Stone].name = "Stone";
	BLOCKS[BlockTypes::Dirt].name = "Dirt";
	BLOCKS[BlockTypes::Log].name = "Wood";
	BLOCKS[BlockTypes::Leaves].name = "Leaves";
	BLOCKS[BlockTypes::Sand].name = "Sand";
	BLOCKS[BlockTypes::Water].name = "Water";
	BLOCKS[BlockTypes::ShubiumCrystal].name = "Shubium Crystal";
	BLOCKS[BlockTypes::Cactus].name = "Shubium Crystal";

					
	BLOCKS[BlockTypes::Grass].drops = BlockTypes::Dirt;
	BLOCKS[BlockTypes::ShubiumOre].drops = BlockTypes::ShubiumCrystal;
	BLOCKS[BlockTypes::Stone].drops = BlockTypes::Stone;
	BLOCKS[BlockTypes::Dirt].drops = BlockTypes::Dirt;
	BLOCKS[BlockTypes::Log].drops = BlockTypes::Log;
	BLOCKS[BlockTypes::Leaves].drops = BlockTypes::Air;
	BLOCKS[BlockTypes::Sand].drops = BlockTypes::Sand;
	BLOCKS[BlockTypes::Water].drops = BlockTypes::Air;
	BLOCKS[BlockTypes::Cactus].drops = BlockTypes::Air;

	
}

