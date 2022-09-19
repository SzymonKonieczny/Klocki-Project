#include "Chunk.h"
#include "ChunkMenager.h"
#include "World.h"
#include "Util.h"
Chunk::Chunk(glm::vec2 ChunkCoords, ChunkMenager* ChunkMenager_)
{
	ChunkPos = ChunkCoords;
	chunkMenager = ChunkMenager_;
}

void Chunk::Generate(int height_)
{

	//std::cout << "Generating chunk Pos:" << ChunkPos.x << ' ' << ChunkPos.y << std::endl;
	int height = height_;
	FastNoise::SmartNode<FastNoise::Simplex> fnSimplex;
	FastNoise::SmartNode<FastNoise::FractalFBm>  fnFractal;
	FastNoise::SmartNode<> fnGenerator;
	fnSimplex = FastNoise::New<FastNoise::Simplex>();
	fnFractal = FastNoise::New<FastNoise::FractalFBm>();

	fnFractal->SetSource(fnSimplex);
	fnFractal->SetOctaveCount(1);
	fnGenerator = FastNoise::NewFromEncodedNodeTree("DQAFAAAAAAAAQAgAAAAAAD8AAAAAAA==");

	std::vector<float> noiseOutput(ChunkSize* ChunkSize);
	fnGenerator->GenUniformGrid2D(noiseOutput.data(), ChunkPos.x * ChunkSize, ChunkPos.y * ChunkSize, ChunkSize, ChunkSize,  0.02,map_seed);


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
					if (Util::GetInstance()->random(0, 1000) < 2) GenerateTree(glm::vec3(j, k, i));
					else setblock(glm::vec3(j, k, i), BlockTypes::Grass);
						//setblock(glm::vec3(j, k, i), Util::GetInstance()->random(0, 9));
					
				
				}
				else setblock(glm::vec3(j, k, i), BlockTypes::Stone);
				
			}


		}
	}
	UpdateBlocksFromBlockQueueMap(false);
	
}

void Chunk::UpdateMesh()
{
	
	meshed = false;
	mesh.verticiesSetNotReady();

	VertexMutex.lock();
	BlocksMutex.lock();
	//std::cout << "Meshing chunk Pos:" << ChunkPos.x << ' ' << ChunkPos.y << std::endl;

	mesh.ClearVerticies();

	std::shared_ptr<Chunk> XMinusChunk;
	std::shared_ptr<Chunk> XPlusChunk;
	std::shared_ptr<Chunk> ZMinusChunk;
	std::shared_ptr<Chunk> ZPlusChunk;
	auto temp = chunkMenager->ChunkMap.find(ChunkPos + glm::vec2(-1, 0));
	(temp != chunkMenager->ChunkMap.end()) ? XMinusChunk = temp->second : XMinusChunk = nullptr;

	temp = chunkMenager->ChunkMap.find(ChunkPos + glm::vec2(1, 0));
	(temp != chunkMenager->ChunkMap.end()) ? XPlusChunk = temp->second : XPlusChunk = nullptr;

	temp = chunkMenager->ChunkMap.find(ChunkPos + glm::vec2(0, -1));
	(temp != chunkMenager->ChunkMap.end()) ? ZMinusChunk = temp->second : ZMinusChunk = nullptr;

	temp = chunkMenager->ChunkMap.find(ChunkPos + glm::vec2(0, 1));
	(temp != chunkMenager->ChunkMap.end()) ? ZPlusChunk = temp->second : ZPlusChunk = nullptr;

	bool queuedXminus = false;
	bool queuedXplus = false;
	bool queuedZminus = false;
	bool queuedZplus = false;

	for (int i =0; i < Blocks.size(); i++)
	{
		
	//	glm::vec3 Pos((ChunkPos.x*ChunkSize) + Blocks[i].LocalPos.x, Blocks[i].LocalPos.y, (ChunkPos.y * ChunkSize) + Blocks[i].LocalPos.z);
		bool meshXminus = true;
		bool meshXplus = true;
		bool meshZminus = true;
		bool meshZplus = true;

		if (Blocks[i].LocalPos.x == 15)
		{
			if (XPlusChunk != nullptr && XPlusChunk->generated)
			{
				Block* b = XPlusChunk->vec3ToBlock(glm::vec3(0, Blocks[i].LocalPos.y, Blocks[i].LocalPos.z));
				if (b != nullptr && Util::GetInstance()->BLOCKS[b->ID].Solid)
				{
					queuedXplus = true;
					meshXplus = false;
				}
			}

		}
		if (Blocks[i].LocalPos.x == 0)
		{
			if (XMinusChunk!= nullptr && XMinusChunk->generated)
			{
				Block* b = XMinusChunk->vec3ToBlock(glm::vec3(15, Blocks[i].LocalPos.y, Blocks[i].LocalPos.z));
				if (b != nullptr && Util::GetInstance()->BLOCKS[b->ID].Solid)
				{	
					queuedXminus = true;
					meshXminus = false;
				}
			
			}
		}

		if (Blocks[i].LocalPos.z == 15)
		{
			if (ZPlusChunk != nullptr && ZPlusChunk->generated)
			{
				Block* b = ZPlusChunk->vec3ToBlock(glm::vec3(Blocks[i].LocalPos.x, Blocks[i].LocalPos.y, 0));
			  	if (b != nullptr && Util::GetInstance()->BLOCKS[b->ID].Solid) 
				{
					queuedZplus = true;
					meshZplus = false;
				}
			}

		}
		if (Blocks[i].LocalPos.z == 0)
		{
			if (ZMinusChunk != nullptr && ZMinusChunk->generated)
			{
				Block* b = ZMinusChunk->vec3ToBlock(glm::vec3(Blocks[i].LocalPos.x, Blocks[i].LocalPos.y, 15));
			 	if (b != nullptr && Util::GetInstance()->BLOCKS[b->ID].Solid)
				{
					queuedZminus = true;
					 meshZminus = false;
				}
			}
		}

		Block* neighbour = vec3ToBlock(Blocks[i].LocalPos + glm::vec3(0.0f, 1.0f, 0.0f));
		if (neighbour == nullptr || !Util::GetInstance()->BLOCKS[neighbour->ID].Solid)
																					   FaceBuilder::BuildFace(mesh, Faces::Up, Blocks[i].LocalPos, (BlockTypes)Blocks[i].ID);
		neighbour = vec3ToBlock(Blocks[i].LocalPos + glm::vec3(0.0f, -1.0f, 0.0f));
	    if (neighbour == nullptr || !Util::GetInstance()->BLOCKS[neighbour->ID].Solid) FaceBuilder::BuildFace(mesh, Faces::Down, Blocks[i].LocalPos, (BlockTypes)Blocks[i].ID);
		
	
		neighbour = vec3ToBlock(Blocks[i].LocalPos + glm::vec3(0.0f, 0.0f, 1.0f));
		if (meshZplus)if (neighbour == nullptr || !Util::GetInstance()->BLOCKS[neighbour->ID].Solid) FaceBuilder::BuildFace(mesh, Faces::North, Blocks[i].LocalPos, (BlockTypes)Blocks[i].ID);
	
		neighbour = vec3ToBlock(Blocks[i].LocalPos + glm::vec3(0.0f, 0.0f, -1.0f));
		if (meshZminus) if (neighbour == nullptr || !Util::GetInstance()->BLOCKS[neighbour->ID].Solid) FaceBuilder::BuildFace(mesh, Faces::South, Blocks[i].LocalPos, (BlockTypes)Blocks[i].ID);


		neighbour = vec3ToBlock(Blocks[i].LocalPos + glm::vec3(-1.0f, 0.0f, 0.0f));
		if (meshXminus) if (neighbour == nullptr || !Util::GetInstance()->BLOCKS[neighbour->ID].Solid) FaceBuilder::BuildFace(mesh, Faces::West, Blocks[i].LocalPos, (BlockTypes)Blocks[i].ID);

		
		neighbour = vec3ToBlock(Blocks[i].LocalPos + glm::vec3(1.0f, 0.0f, 0.0f));
		if (meshXplus) if ( neighbour == nullptr || !Util::GetInstance()->BLOCKS[neighbour->ID].Solid) FaceBuilder::BuildFace(mesh, Faces::East, Blocks[i].LocalPos, (BlockTypes)Blocks[i].ID);



	}
	
	BlocksMutex.unlock();

	VertexMutex.unlock();
	meshed = true;
	mesh.verticiesSetReady();
		

			// causes a cascade of remeshes
	//if (queuedXminus)chunkMenager->world->AddChunksMeshToUpdate(XMinusChunk->ChunkPos);
	//if (queuedXplus )chunkMenager->world->AddChunksMeshToUpdate(XPlusChunk->ChunkPos);
	//if (queuedZminus)chunkMenager->world->AddChunksMeshToUpdate(ZMinusChunk->ChunkPos);
	//if (queuedZplus )chunkMenager->world->AddChunksMeshToUpdate(ZPlusChunk->ChunkPos);
	

	
	

}

bool Chunk::CheckIfSolidBlock(glm::vec3 Pos)
{

	Block* blockptr = vec3ToBlock(Pos);
	
	if (blockptr == nullptr)
	{

		return false;

	}
	if (!Util::GetInstance()->BLOCKS[blockptr->ID].Solid)
	{
	
		return true;
	}

	return false;
}



void Chunk::Draw(Shader& shader)
{
	if (meshed)
	{
		if (VertexMutex.try_lock())
		{
		mesh.Draw(shader, glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),true);
		VertexMutex.unlock();	
		}

	}

}

	

bool Chunk::setblock(glm::vec3 LocPos, int ID)
{// returns true if the placement was succesful

		if (!isPositionViable(LocPos))
		{ 

			//std::cout << "Not a viable position. Block requested at " << LocPos.x << " " << LocPos.y + '\n';
			/*
			|-------------------------------------------------------------------|
			|																	|
			|			MAKE A TERRAIN GENERATOR FOR THIS						|
			|		  what is below is a TEMPORARY solution						|
			|		Instead of chunk building themselves, a generator should	|
			|			And it should use the ChunkMenagers functions			|
			|-------------------------------------------------------------------|
			*/
			std::cout << "Not a viable position. Block requested at " << LocPos.x << " " << LocPos.y + '\n';
			std::cout << "THIS SHOULD NOT HAPPEN '\n'";
			return false;
			
		}
		LockBlockMutex();
		LocPos = glm::floor(LocPos);
		if (block_map.find(glm::vec3(LocPos.x, LocPos.y, LocPos.z)) != block_map.end())
		{
			Blocks[block_map[glm::vec3(LocPos.x, LocPos.y, LocPos.z)]].ID = ID;
		}
		else
		{
			//Blocks.push_back(ID);
			Blocks.push_back(Block{ glm::vec3(LocPos.x, LocPos.y, LocPos.z), ID });
			block_map.insert(std::make_pair(glm::vec3(LocPos.x, LocPos.y, LocPos.z), Blocks.size() - 1));

		}

		UnlockBlockMutex();

	return true;
}



	void Chunk::GenerateTree(glm::vec3 LocPos, glm::vec3 Dir, int branches)
	{
		if (Util::GetInstance()->random(1, 10) > 7 || branches <=0)return;
		glm::vec3 Up(0, 1, 0);
		setblock(LocPos, 4);
		for (int i = 0; i < 3; i++)
		{
			LocPos += Up;
			setblock(LocPos, 4);


		}
		GenerateTree(LocPos, glm::vec3(Util::GetInstance()->random(-1, 1), 0, Util::GetInstance()->random(-1, 1)), branches-2);
		int rand = Util::GetInstance()->random(1, 3);
		for (int i = 0; i < rand; i++)
		{
			GenerateTree(LocPos, glm::vec3(Util::GetInstance()->random(-1, 1), 0, Util::GetInstance()->random(-1, 1)), branches - 1);
		}
		for (int i = 0; i < 4; i++)
		{
			LocPos += Up + Dir;
			setblock(LocPos, 4);

			setblock(LocPos + glm::vec3(1, 0, 0), 5);
			setblock(LocPos + glm::vec3(0, 0, 1), 5);
			setblock(LocPos + glm::vec3(-1, 0, 0), 5);
			setblock(LocPos + glm::vec3(0, 0, -1), 5);
		}
		GenerateTree(LocPos, glm::vec3(Util::GetInstance()->random(-1, 1), 0, Util::GetInstance()->random(-1, 1)), branches - 1);
		 rand = Util::GetInstance()->random(1, 3);
		for (int i = 0; i < rand; i++)
		{
			GenerateTree(LocPos, glm::vec3(Util::GetInstance()->random(-1, 1), 0, Util::GetInstance()->random(-1, 1)), branches - 2);
		}

		/*for (int y = 0; y < 3; y++)
		{
			glm::vec3 LeavesPos = LocPos;

			for (int i = -3; i <= 3; i++)
			{

				for (int k = -3; k <= 3; k++)
				{
					if (k == 0 && i == 0) continue;
					LeavesPos += glm::vec3(i, y, k);
					setblock(LeavesPos, 5);

				}

			}

		}*/
		
	}


	bool Chunk::isPositionViable(glm::vec3 LocPos)
{
	return !(LocPos.x > ChunkSize - 1 || LocPos.x < 0 || LocPos.y < 0 || LocPos.y > ChunkHeight - 1
		|| LocPos.z > ChunkSize - 1 || LocPos.z < 0);

}

void Chunk::UpdateBlocksFromBlockQueueMap(bool JustNewBlocks)
{

	auto it = chunkMenager->BlockQueuesMap.find(ChunkPos);
	if (it != chunkMenager->BlockQueuesMap.end())
	{
	
		//Blocks.insert(Blocks.end(), it->second.begin(), it->second.end());
		for (Block b : it->second)
		{
			setblock(b.LocalPos, b.ID);
		}
		//if (JustNewBlocks)UpdateMeshOnlyAdd(it->second);
		//else UpdateMesh();
	

	}
	generated = true; // here coz Generator calls it
	chunkMenager->world->AddChunksMeshToUpdate(ChunkPos);

}

Block* Chunk::vec3ToBlock(glm::vec3 LocPos)
{
	if (!isPositionViable(LocPos))return nullptr;
	LocPos = glm::floor(LocPos);
	auto search_result = block_map.find(LocPos);
	//std::cout << "search_result: " << LocPos.x << ' ' << LocPos.y << ' ' << LocPos.z << '\n';
	if (search_result != block_map.end())
	{
		

		return &Blocks[(*search_result).second];
	}
	else return nullptr;

}

Chunk::~Chunk()
{
	std::cout << "Yeeting chunk Pos:" << ChunkPos.x << ' ' << ChunkPos.y << std::endl;
	
	

	/*for (int i = 0; i < 16; i++)
		delete[] column_heights[i];
	
	delete[] column_heights;*/
	
}

void Chunk::LockBlockMutex()
{
	BlocksMutex.lock();
}
void Chunk::UnlockBlockMutex()
{
	BlocksMutex.unlock();
}
