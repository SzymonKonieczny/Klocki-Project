#include "FlatTerrainGenerator.h"
void FlatTerrainGenerator::Generate(std::shared_ptr<Chunk> chunkptr)
{

	{
		//std::cout << "Generating chunk Pos:" << chunkptr->ChunkPos.x << ' ' << chunkptr->ChunkPos.y << std::endl;

		int column_height = 5;

		for (int i = 0; i < ChunkSize; i++) //i = Z coordinate
		{


			for (int j = 0; j < ChunkSize; j++) // j = X coordinate
			{

				for (int k = 0; k <= column_height; k++) // k = Y coordinate
				{

					if (k == column_height)
					{
						chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Grass);
					}
					else chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Stone);

				}


			}
		}


		chunkptr->UpdateBlocksFromBlockQueueMap(true);
	}
}
void FlatTerrainGenerator::GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir, int branches)
{
}
FlatTerrainGenerator::FlatTerrainGenerator(ChunkMenager* menager) : BaseTerrainGenerator(menager)
{

}