#include "TerrainGenerator.h"

void TerrainGenerator::Generate(std::shared_ptr<Chunk> chunkptr)
{

	//chunkptr->LockBlockMutex(); SetBlock locks it anyways

	//std::cout << "Generating chunk Pos:" << chunkptr->ChunkPos.x << ' ' << chunkptr->ChunkPos.y << std::endl;
	glm::vec3 HousePos;
	bool shoudHouseGenerate = false;

	std::vector<float> noiseOutput(ChunkSize * ChunkSize);
	fnGenerator->GenUniformGrid2D(noiseOutput.data(), chunkptr->ChunkPos.x * ChunkSize, chunkptr->ChunkPos.y * ChunkSize, ChunkSize, ChunkSize, 0.02, map_seed);


	int index = 0;
	for (int i = 0; i < ChunkSize; i++) //i = Z coordinate
	{


		for (int j = 0; j < ChunkSize; j++) // j = X coordinate
		{
			int column_height = ((noiseOutput[index++] + 1) / 2) * 20 + 35;
			for (int k = 0; k <= column_height; k++) // k = Y coordinate
			{

				if (k == column_height)
				{
					if (k < 20 && k == column_height) chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Sand);
					else
					{
						if (Util::GetInstance()->random(0, 500) < 1) GenerateTree(Util::LocPosAndChunkPosToWorldPos(glm::vec3(j, k, i), chunkptr->ChunkPos));
						else
						{
							chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Grass);
							if (Util::GetInstance()->random(0,1000) < 1)
							{
								shoudHouseGenerate = true;
								HousePos = Util::LocPosAndChunkPosToWorldPos( glm::vec3(j, k, i), chunkptr->ChunkPos);
							}
						}
						
						//setblock(glm::vec3(j, k, i), Util::GetInstance()->random(0, 9));

					}
					

				}

				else
				{ 
					 chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Stone);
				}
				

			}


		}
	}
	//chunkptr->UnlockBlockMutex();
	if (shoudHouseGenerate) TryToGenerateHouse(HousePos);
	chunkptr->UpdateBlocksFromBlockQueueMap(true);

}
void TerrainGenerator::GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir, int branches)
{
	if (Util::GetInstance()->random(1, 10) > 7 || branches <= 0)return;
	//glm::vec3 WorldPos = Util::LocPosAndChunkPosToWorldPos(LocPos,ChunkPos);
	glm::vec3 Up(0, 1, 0);
	 chunkmenager->SetBlockInWorld(WorldPos,BlockTypes::Log);
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

		chunkmenager->SetBlockInWorld(WorldPos,  BlockTypes::Leaves);

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
void TerrainGenerator::TryToGenerateHouse(glm::vec3 WorldPos)
{
	
	/*for (int x = 0; x < 7; x++) //Check if empty Space
	{
		for (int z = 0; z < 7; z++)
		{
			Block* b = chunkmenager->GetBlockInWorld(glm::vec3(WorldPos.x - x, WorldPos.y, WorldPos.z - z));
			if (b != nullptr)
			{
				if (Util::GetInstance()->BLOCKS[b->ID].Solid) return;

			}

		}
	}*/
	
	for (int x = 0; x < 7; x++) //Floor
	{
		for (int z = 0; z < 7; z++)
		{
			chunkmenager->SetBlockInWorld(glm::vec3(WorldPos.x - x, WorldPos.y-1, WorldPos.z - z), BlockTypes::Stone);
		}
	}
	
		for (int y = 0; y < 4; y++) // part 1 of the box
		{	for (int xz = 0; xz < 7; xz++)
			{
				chunkmenager->SetBlockInWorld(glm::vec3(WorldPos.x, WorldPos.y + y, WorldPos.z - xz), BlockTypes::Log);
				chunkmenager->SetBlockInWorld(glm::vec3(WorldPos.x - xz, WorldPos.y + y, WorldPos.z ), BlockTypes::Log);
			}
		}
		WorldPos -= glm::vec3(7, 0, 7);
		for (int y = 0; y < 4; y++)
		{
			for (int xz = 0; xz < 7; xz++)
			{
				chunkmenager->SetBlockInWorld(glm::vec3(WorldPos.x, WorldPos.y + y, WorldPos.z + xz), BlockTypes::Log);
				chunkmenager->SetBlockInWorld(glm::vec3(WorldPos.x + xz, WorldPos.y + y, WorldPos.z), BlockTypes::Log);
			}
		}

	

}
TerrainGenerator::TerrainGenerator(ChunkMenager* menager) : BaseTerrainGenerator(menager)
{
	//DQACAAAAzczMPQ0AAgAAAI/CNUAIAAAUrjdBADMzMz8Aj8KBQQBSuB7A
	//EwCPwnU/DQADAAAAAAAAQA0AAgAAAHE9ikAFAAAAAAAAAAAAAAAAAAAAAAAAAAAAAI/Cdb0AUrhOQQEIAAAAAAAA
	fnGenerator = FastNoise::NewFromEncodedNodeTree("DQACAAAAzczMPQ0AAgAAAI/CNUAIAAAUrjdBADMzMz8Aj8KBQQBSuB7A");
}
TerrainGenerator::~TerrainGenerator()
{
	std::cout << "Train Generator is being destroyed" << std::endl;
}