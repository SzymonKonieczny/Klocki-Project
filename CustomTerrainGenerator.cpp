#include "CustomTerrainGenerator.h"
/*void CustomTerrainGenerator::Generate(std::shared_ptr<Chunk> chunkptr)
{

}*/

void CustomTerrainGenerator::Generate(std::shared_ptr<Chunk> chunkptr)
{
	std::cout << "Generating chunk Pos:" << chunkptr->ChunkPos.x << ' ' << chunkptr->ChunkPos.y << std::endl;


	std::vector<float> noiseOutput(ChunkSize * ChunkSize);
	fnGenerator->GenUniformGrid2D(noiseOutput.data(), chunkptr->ChunkPos.x * ChunkSize, chunkptr->ChunkPos.y * ChunkSize, ChunkSize, ChunkSize, 0.02, map_seed);


	int index = 0;
	for (int i = 0; i < ChunkSize; i++) //i = Z coordinate
	{


		for (int j = 0; j < ChunkSize; j++) // j = X coordinate
		{
			int column_height = ((noiseOutput[index++] + 1) / 2) * 30 + 15;
			for (int k = 0; k <= column_height; k++) // k = Y coordinate
			{

				if (k == column_height)
				{
					if (Util::GetInstance()->random(0, 50) < 1) GenerateTree(Util::LocPosAndChunkPosToWorldPos(glm::vec3(j, k, i), chunkptr->ChunkPos));
					else
						chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Grass);
					//setblock(glm::vec3(j, k, i), Util::GetInstance()->random(0, 9));


				}
				else chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Stone);

			}


		}
	}
	//chunkptr->UnlockBlockMutex();

	chunkptr->UpdateBlocksFromBlockQueueMap(true);
}

void CustomTerrainGenerator::GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir, int branches)
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

	for (int y = 0; y < 2; y++)
	{
		for (int i = -2; i <= 2; i++)
		{
				for (int k = -2; k <= 2; k++)
				{
					if (k == 0 && i == 0) chunkmenager->SetBlockInWorld(WorldPos, BlockTypes::Log);
					else  chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(i, 0, k), BlockTypes::Leaves);
				}
		}
		WorldPos += Up;
	}
	for (int y = 0; y < 2; y++)
	{
		for (int i = -1; i <= 1; i++)
		{

			for (int k = -1; k <= 1; k++)
			{
				chunkmenager->SetBlockInWorld(WorldPos + glm::vec3(i, 0, k), BlockTypes::Leaves);

			}
		}
		WorldPos += Up;
	}



}

CustomTerrainGenerator::CustomTerrainGenerator(ChunkMenager* menager) : BaseTerrainGenerator(menager)
{
	fnGenerator = FastNoise::NewFromEncodedNodeTree("DQACAAAAhetRPw0AAgAAAMP1KD8IAABSuEZBAI/C9b0A16OwPwBcjyLA");
	//DQACAAAAzczMPQ0AAgAAAI/CNUAIAAAUrjdBADMzMz8Aj8KBQQBSuB7A

	//fnGenerator = FastNoise::NewFromEncodedNodeTree("DQAFAAAAAAAAQAgAAAAAAD8AAAAAAA==");


}
