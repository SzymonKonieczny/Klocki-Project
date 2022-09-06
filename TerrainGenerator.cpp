#include "TerrainGenerator.h"

void TerrainGenerator::Generate(std::shared_ptr<Chunk> chunkptr)
{

	chunkptr->LockBlockMutex();

	std::cout << "Generating chunk Pos:" << chunkptr->ChunkPos.x << ' ' << chunkptr->ChunkPos.y << std::endl;


	std::vector<float> noiseOutput(ChunkSize * ChunkSize);
	fnGenerator->GenUniformGrid2D(noiseOutput.data(), chunkptr->ChunkPos.x * ChunkSize, chunkptr->ChunkPos.y * ChunkSize, ChunkSize, ChunkSize, 0.02, map_seed);


	int index = 0;
	for (int i = 0; i < ChunkSize; i++) //i = Z coordinate
	{


		for (int j = 0; j < ChunkSize; j++) // j = X coordinate
		{
			int column_height = ((noiseOutput[index++] + 1) / 2) * 20 + 5;
			for (int k = 0; k <= column_height; k++) // k = Y coordinate
			{

				if (k == column_height)
				{
					if (Util::GetInstance()->random(0, 10) < 1) GenerateTree(Util::LocPosAndChunkPosToWorldPos(glm::vec3(j, k, i), chunkptr->ChunkPos));
					else 
					chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Grass);
					//setblock(glm::vec3(j, k, i), Util::GetInstance()->random(0, 9));


				}
				else chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Stone);

			}


		}
	}
	chunkptr->UnlockBlockMutex();

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
TerrainGenerator::TerrainGenerator(ChunkMenager* menager)
{
	chunkmenager = menager;
	fnSimplex = FastNoise::New<FastNoise::Simplex>();
	fnFractal = FastNoise::New<FastNoise::FractalFBm>();

	fnFractal->SetSource(fnSimplex);
	fnFractal->SetOctaveCount(5);
	fnGenerator = FastNoise::NewFromEncodedNodeTree("DQAFAAAAAAAAQAgAAAAAAD8AAAAAAA==");
}
TerrainGenerator::~TerrainGenerator()
{
	std::cout << "Train Generator is being destroyed" << std::endl;
}