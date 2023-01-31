#include "TerrainGenerator.h"

bool TerrainGenerator::isInOneBiome(NoiseMaps& maps)
{
	
	return (DecideBiome( maps.noiseOutputBiome[0])==
		DecideBiome(maps.noiseOutputBiome[15]) && DecideBiome(maps.noiseOutputBiome[240]) == DecideBiome(maps.noiseOutputBiome[15]) &&
		DecideBiome(maps.noiseOutputBiome[240]) == 
		DecideBiome(maps.noiseOutputBiome[255]));
}

void TerrainGenerator::GenerateNormally(NoiseMaps& Noises, std::shared_ptr<Chunk> chunkptr)
{
	int index = 0;
	for (int i = 0; i < ChunkSize; i++) //i = Z coordinate
	{


		for (int j = 0; j < ChunkSize; j++) // j = X coordinate
		{
			int column_height;
			float BiomeAtBlock = (Noises.noiseOutputBiome[index] + 1.f) / 2.f;
			BIOMES Biome;
			if (BiomeAtBlock < 0.5) Biome = BIOMES::Desert;
			else
			{
				if (BiomeAtBlock < 0.55)Biome = BIOMES::Forest;
				else Biome = BIOMES::Forest; //Moiuntain
			}

			switch (Biome)
			{
			case BIOMES::Forest:

				column_height = ((Noises.noiseOutputForest[index++] + 1) / 2) * 20 + 30;
				break;
			case BIOMES::Desert:

				column_height = ((Noises.noiseOutputDesert[index++] + 1) / 2) * 20 + 15;

				break;
			case BIOMES::Mountain:
				column_height = ((Noises.noiseOutputMountain[index++] + 1) * 70 / 2) + 20;

				break;
			default:
				column_height = 5;
				index++;
				break;
			}

			chunkptr->column_heights[j][i] = column_height;

			//
			//			NOTE TO SELF
			//		TAKE EXTREME VALUES OF THE NOISE FUNCTIONS (AT 0,0;15,0;0,15;15,15) AND
			//	INTERPOLATE FOR ALL THE REST AS LERP(0,0,1/16); 
			//		or something idk 
			// 	https://pl.wikipedia.org/wiki/Interpolacja_dwuliniowa
			// 
			//
			for (int k = 0; k <= column_height; k++) // k = Y coordinate
			{

				switch (Biome)
				{
				case BIOMES::Forest:
					chunkptr->setblock(glm::vec3(j, k, i), Forest.GetBlockTypeAt(glm::vec3(j, k, i), k == column_height));
					if (k == column_height) Forest.GenerateFeatures(Util::LocPosAndChunkPosToWorldPos(glm::vec3(j, k, i),
						chunkptr->ChunkPos));

					break;
				case BIOMES::Desert:
					chunkptr->setblock(glm::vec3(j, k, i), Desert.GetBlockTypeAt(glm::vec3(j, k, i), k == column_height));
					if (k == column_height) Desert.GenerateFeatures(Util::LocPosAndChunkPosToWorldPos(glm::vec3(j, k, i),
						chunkptr->ChunkPos));

					break;
				case BIOMES::Mountain:
					chunkptr->setblock(glm::vec3(j, k, i), Mountain.GetBlockTypeAt(glm::vec3(j, k, i), k == column_height));
					if (k == column_height) Mountain.GenerateFeatures(Util::LocPosAndChunkPosToWorldPos(glm::vec3(j, k, i),
						chunkptr->ChunkPos));

					break;
				default:
					chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Log);
					break;
				}



				/*if (k == column_height)
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
				}*/


			}


		}
	}

	//std::cout << "Amount of uses of the mutex " << chunkptr->Amount_of_Blockmutex_Uses << '\n';
	//if(chunkptr->Amount_of_Blockmutex_Uses< 9999)std::cout << "Amount of uses of the mutex " << chunkptr->Amount_of_Blockmutex_Uses << '\n';
	//else 
	//	std::cout << "BIG Amount of uses of the mutex " << chunkptr->Amount_of_Blockmutex_Uses << " At chunk : " << chunkptr->ChunkPos.x << ' ' << chunkptr->ChunkPos.y << std::endl;;

}

void TerrainGenerator::GenerateOnBiomeEdge(NoiseMaps& Noises, std::shared_ptr<Chunk> chunkptr)
{
	std::vector<float> ColumnHeightFromNoises(4);


	int indiciesWeAreInterestedIn[] = { 0,240,15,255 };
	for (int i = 0; i < 4; i++)
	{
		float* Qptrs[4] = { &chunkptr->q11, &chunkptr->q12 ,&chunkptr->q21 ,&chunkptr->q22 }; //stinky cheese


		switch (DecideBiome(Noises.noiseOutputBiome[indiciesWeAreInterestedIn[i]]))
		{
		case BIOMES::Forest:
			ColumnHeightFromNoises[i] = Noises.noiseOutputForest[indiciesWeAreInterestedIn[i]];
			*Qptrs[i] = ((ColumnHeightFromNoises[i] + 1) / 2) * 20 + 30;
			break;

		case BIOMES::Desert:
			ColumnHeightFromNoises[i] = Noises.noiseOutputDesert[indiciesWeAreInterestedIn[i]];
			*Qptrs[i] = ((ColumnHeightFromNoises[i] + 1) / 2) * 20 + 15;

			break;

		case BIOMES::Mountain:
			ColumnHeightFromNoises[i] = Noises.noiseOutputMountain[indiciesWeAreInterestedIn[i]];
			*Qptrs[i] = ((ColumnHeightFromNoises[i] + 1) / 2) * 20 + 20;

			break;
		}
	}


	int index = 0;

	//chunkptr->q11 = ((ColumnHeightFromNoises[0] + 1) / 2) * 20;
	//chunkptr->q12 = ((ColumnHeightFromNoises[1] + 1) / 2) * 20;
	//chunkptr->q21 = ((ColumnHeightFromNoises[2] + 1) / 2) * 20;
	//chunkptr->q22 = ((ColumnHeightFromNoises[3] + 1) / 2) * 20;

	 float q11 = chunkptr->q11;
	 float q12 = chunkptr->q12;
	 float q21 = chunkptr->q21;
	 float q22 = chunkptr->q22;
	for (int i = 0; i < ChunkSize; i++) //i = Z coordinate
	{


		for (int j = 0; j < ChunkSize; j++) // j = X coordinate
		{
			int column_height;
			BIOMES Biome = DecideBiome(Noises.noiseOutputBiome[index]);



			switch (Biome)
			{
			case BIOMES::Forest:




				column_height = ( Util::BilinearInterpolation(q11, q12, q21, q22, glm::vec2(0,0), glm::vec2(15, 15), glm::vec2(j,i)));


				index++;
				break;
			case BIOMES::Desert:
				column_height = ( Util::BilinearInterpolation(q11, q12, q21, q22, glm::vec2(0, 0), glm::vec2(15, 15), glm::vec2(j, i)));
				index++;


				break;
			case BIOMES::Mountain:

				column_height = (Util::BilinearInterpolation(q11, q12, q21, q22, glm::vec2(0, 0), glm::vec2(15, 15), glm::vec2(j, i)));
				index++;


				break;
			default:
				column_height = 5;
				index++;
				break;
			}

			chunkptr->column_heights[j][i] = column_height;

			//
			//			NOTE TO SELF
			//		TAKE EXTREME VALUES OF THE NOISE FUNCTIONS (AT 0,0;15,0;0,15;15,15) AND
			//	INTERPOLATE FOR ALL THE REST AS LERP(0,0,1/16); 
			//		or something idk 
			// 	https://pl.wikipedia.org/wiki/Interpolacja_dwuliniowa
			// 
			//

			for (int k = 0; k <= column_height; k++) // k = Y coordinate
			{

				switch (Biome)
				{
				case BIOMES::Forest:
					chunkptr->setblock(glm::vec3(j, k, i), Forest.GetBlockTypeAt(glm::vec3(j, k, i), k == column_height));
					if (k == column_height) Forest.GenerateFeatures(Util::LocPosAndChunkPosToWorldPos(glm::vec3(j, k, i),
						chunkptr->ChunkPos));

					break;
				case BIOMES::Desert:
					chunkptr->setblock(glm::vec3(j, k, i), Desert.GetBlockTypeAt(glm::vec3(j, k, i), k == column_height));
					if (k == column_height) Desert.GenerateFeatures(Util::LocPosAndChunkPosToWorldPos(glm::vec3(j, k, i),
						chunkptr->ChunkPos));

					break;
				case BIOMES::Mountain:
					chunkptr->setblock(glm::vec3(j, k, i), Mountain.GetBlockTypeAt(glm::vec3(j, k, i), k == column_height));
					if (k == column_height) Mountain.GenerateFeatures(Util::LocPosAndChunkPosToWorldPos(glm::vec3(j, k, i),
						chunkptr->ChunkPos));

					break;
				default:
					chunkptr->setblock(glm::vec3(j, k, i), BlockTypes::Log);
					break;
				}



				/*if (k == column_height)
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
				}*/


			}


		}
	}
}

void TerrainGenerator::Generate(std::shared_ptr<Chunk> chunkptr)
{

	

	//std::cout << "Generating chunk Pos:" << chunkptr->ChunkPos.x << ' ' << chunkptr->ChunkPos.y << std::endl;
	
	NoiseMaps Noises;

	Noises.noiseOutputBiome.resize(ChunkSize * ChunkSize);
	fnGeneratorBiomeOracle->GenUniformGrid2D(Noises.noiseOutputBiome.data(), chunkptr->ChunkPos.x * ChunkSize, chunkptr->ChunkPos.y * ChunkSize, ChunkSize, ChunkSize, 0.02, map_seed);


	Noises.noiseOutputForest.resize(ChunkSize * ChunkSize);
	Forest.NoiseFunc->GenUniformGrid2D(Noises.noiseOutputForest.data(), chunkptr->ChunkPos.x * ChunkSize, chunkptr->ChunkPos.y * ChunkSize, ChunkSize, ChunkSize, 0.02, map_seed);


	Noises.noiseOutputDesert.resize(ChunkSize * ChunkSize);
	Desert.NoiseFunc->GenUniformGrid2D(Noises.noiseOutputDesert.data(), chunkptr->ChunkPos.x * ChunkSize, chunkptr->ChunkPos.y * ChunkSize, ChunkSize, ChunkSize, 0.02, map_seed);

	Noises.noiseOutputMountain.resize(ChunkSize * ChunkSize);
	Mountain.NoiseFunc->GenUniformGrid2D(Noises.noiseOutputMountain.data(), chunkptr->ChunkPos.x * ChunkSize, chunkptr->ChunkPos.y * ChunkSize, ChunkSize, ChunkSize, 0.02, map_seed);

	if (isInOneBiome(Noises)) GenerateNormally(Noises, chunkptr);
	else GenerateOnBiomeEdge(Noises, chunkptr);
	
	chunkptr->UpdateBlocksFromBlockQueueMap(true);

}
BIOMES TerrainGenerator::DecideBiome(float BiomeNoiseOutput)
{
	float BiomeAtBlock = (BiomeNoiseOutput + 1.f) / 2.f;

	BIOMES Biome;
	if (BiomeAtBlock < 0.5) Biome = BIOMES::Desert;
	else
	{
		if (BiomeAtBlock < 0.55)Biome = BIOMES::Forest;
		else Biome = BIOMES::Mountain; //Moiuntain
	}

	return Biome;
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
TerrainGenerator::TerrainGenerator(ChunkMenager* menager) : BaseTerrainGenerator(menager), Forest(chunkmenager), Desert(chunkmenager), Mountain(chunkmenager)
{
	
	
	

	fnGeneratorBiomeOracle = FastNoise::NewFromEncodedNodeTree("EwCPwnU9DQACAAAAAAAAAA0ABgAAAOxROD4JAAAAAIA/AArXIz8AAACAPwDsUfhA");
	//EwApXA8+DQAQAAAAw/UoPw0AAgAAAAAAAEAJAAAAAIA/AAAAAD8AAACAPwAAAAAA
	//DQACAAAAzczMPQ0AAgAAAI/CNUAIAAAUrjdBADMzMz8Aj8KBQQBSuB7A
	//EwCPwnU/DQADAAAAAAAAQA0AAgAAAHE9ikAFAAAAAAAAAAAAAAAAAAAAAAAAAAAAAI/Cdb0AUrhOQQEIAAAAAAAA
	//fnGenerator = FastNoise::NewFromEncodedNodeTree("DQACAAAAzczMPQ0AAgAAAI/CNUAIAAAUrjdBADMzMz8Aj8KBQQBSuB7A");
}
TerrainGenerator::~TerrainGenerator()
{
	std::cout << "Train Generator is being destroyed" << std::endl;
}