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

			BLOCKS.push_back(BlockTemplate({ testingX,testingY ,true , "Unnamed", BlockType::Air }));
			loadedAmout++;
			if (loadedAmout >= amoutOfBlocks) break;
		}
	}
	//Here load properties of every block.
	BLOCKS[BlockType::Air].Collidable = false;
	BLOCKS[BlockType::Water].Collidable = false;

	BLOCKS[BlockType::Grass].name = "Grass Block";
	BLOCKS[BlockType::ShubiumOre].name = "Shubium Ore";
	BLOCKS[BlockType::Stone].name = "Stone";
	BLOCKS[BlockType::Dirt].name = "Dirt";
	BLOCKS[BlockType::Log].name = "Wood";
	BLOCKS[BlockType::Leaves].name = "Leaves";
	BLOCKS[BlockType::Sand].name = "Sand";
	BLOCKS[BlockType::Water].name = "Water";
	BLOCKS[BlockType::ShubiumCrystal].name = "Shubium Crystal";

	BLOCKS[BlockType::Grass].drops = BlockType::Dirt;
	BLOCKS[BlockType::ShubiumOre].drops = BlockType::ShubiumCrystal;
	BLOCKS[BlockType::Stone].drops = BlockType::Stone;
	BLOCKS[BlockType::Dirt].drops = BlockType::Dirt;
	BLOCKS[BlockType::Log].drops = BlockType::Log;
	BLOCKS[BlockType::Leaves].drops = BlockType::Air;
	BLOCKS[BlockType::Sand].drops = BlockType::Sand;
	BLOCKS[BlockType::Water].drops = BlockType::Air;
	
}

