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

	return glm::vec2(int(WorldPos.x/ChunkSize),int(WorldPos.z / ChunkSize));
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

			BLOCKS.push_back(BlockTemplate({ testingX,testingY ,true , "Unnamed", BlockTypes::Air }));
			loadedAmout++;
			if (loadedAmout >= amoutOfBlocks) break;
		}
	}
	//Here load properties of every block.
	BLOCKS[BlockTypes::Air].Collidable = false;
	BLOCKS[BlockTypes::Water].Collidable = false;

	BLOCKS[BlockTypes::Grass].name = "Grass Block";
	BLOCKS[BlockTypes::ShubiumOre].name = "Shubium Ore";
	BLOCKS[BlockTypes::Stone].name = "Stone";
	BLOCKS[BlockTypes::Dirt].name = "Dirt";
	BLOCKS[BlockTypes::Log].name = "Wood";
	BLOCKS[BlockTypes::Leaves].name = "Leaves";
	BLOCKS[BlockTypes::Sand].name = "Sand";
	BLOCKS[BlockTypes::Water].name = "Water";
	BLOCKS[BlockTypes::ShubiumCrystal].name = "Shubium Crystal";
					
	BLOCKS[BlockTypes::Grass].drops = BlockTypes::Dirt;
	BLOCKS[BlockTypes::ShubiumOre].drops = BlockTypes::ShubiumCrystal;
	BLOCKS[BlockTypes::Stone].drops = BlockTypes::Stone;
	BLOCKS[BlockTypes::Dirt].drops = BlockTypes::Dirt;
	BLOCKS[BlockTypes::Log].drops = BlockTypes::Log;
	BLOCKS[BlockTypes::Leaves].drops = BlockTypes::Air;
	BLOCKS[BlockTypes::Sand].drops = BlockTypes::Sand;
	BLOCKS[BlockTypes::Water].drops = BlockTypes::Air;
	
}

