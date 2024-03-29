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

			BLOCKS.push_back(BlockTemplate({ testingX,testingY ,true,true,true , "Unnamed", BlockTypes::Air, BlockShapes::BlockShape, BlockRenderMethod::Solid }));
			loadedAmout++;
			if (loadedAmout >= amoutOfBlocks) break;
		}
	}
	//Here load properties of every block.
	BLOCKS[BlockTypes::Air].Selectable = false;


	BLOCKS[BlockTypes::Air].Collidable = false;
	BLOCKS[BlockTypes::Water].Collidable = false;
	BLOCKS[BlockTypes::Rose].Collidable = false;
	BLOCKS[BlockTypes::Flower].Collidable = false;
	BLOCKS[BlockTypes::DeadBush].Collidable = false;
	BLOCKS[BlockTypes::Lavender].Collidable = false;


	BLOCKS[BlockTypes::Air].Solid = false;
	BLOCKS[BlockTypes::Water].Solid = false;
	BLOCKS[BlockTypes::Leaves].Solid = false;
	BLOCKS[BlockTypes::Rose].Solid = false;
	BLOCKS[BlockTypes::Flower].Solid = false;
	BLOCKS[BlockTypes::DeadBush].Solid = false;
	BLOCKS[BlockTypes::Lavender].Solid = false;



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

	BLOCKS[BlockTypes::Rose].Shape = BlockShapes::CrossShape;
	BLOCKS[BlockTypes::Flower].Shape = BlockShapes::CrossShape;
	BLOCKS[BlockTypes::DeadBush].Shape = BlockShapes::CrossShape;
	BLOCKS[BlockTypes::Lavender].Shape = BlockShapes::CrossShape;


	BLOCKS[BlockTypes::Water].RenderMethod =BlockRenderMethod::Translucent;

}

float Util::LinearInterpolation(float p1, float p2, float t)
{

	return p1 + (t * (p2 - p1));
}

float Util::BilinearInterpolation(float q11, float q12, float q21, float q22, glm::vec2 p1, glm::vec2 p2, glm::vec2 p)
{
	//p1 and p2 are the corners that defince the rectangle, most cases for terrain gen 0,0 and 15,15
	//p is the point you want to get the interpolated value for


	float r1 = ((p2.x - p.x) / (p2.x - p1.x)) * q11 + ((p.x - p1.x) / (p2.x - p1.x)) * q21;
	float r2 = ((p2.x - p.x) / (p2.x - p1.x)) * q12 + ((p.x - p1.x) / (p2.x - p1.x)) * q22;
	return ((p2.y - p.y) / (p2.y - p1.y)) * r1 + ((p.y - p1.y) / (p2.y - p1.y)) * r2;

	

	
	
	
	//return Util::LinearInterpolation(Util::LinearInterpolation(q11, q21, tx), Util::LinearInterpolation(q21, q22, tx), ty);
}



