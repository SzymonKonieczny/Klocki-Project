#include "Chunk.h"
#include "ChunkMenager.h"

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
	Mutex.lock();
	mesh.ClearVerticies();

	for (std::vector<Block>::iterator it = Blocks.begin(); it != Blocks.end(); ++it)
	{
		glm::vec3 Pos((ChunkPos.x*ChunkSize) + it->LocalPos.x, 
			 it->LocalPos.y, 
			(ChunkPos.y * ChunkSize) + it->LocalPos.z);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 1.0f, 0.0f)) == nullptr) FaceBuilder ::BuildFace(mesh.GetVertexVector(), Faces::Up, Pos,(BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, -1.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.GetVertexVector(), Faces::Down, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 0.0f, 1.0f)) == nullptr) FaceBuilder::BuildFace( mesh.GetVertexVector(), Faces::North, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 0.0f, -1.0f)) == nullptr) FaceBuilder::BuildFace(mesh.GetVertexVector(), Faces::South, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(-1.0f, 0.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.GetVertexVector(), Faces::West, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(1.0f, 0.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace( mesh.GetVertexVector(), Faces::East, Pos, (BlockTypes)it->ID);


	}
	
	/*mesh.vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(0.5f, 0.5f, 0.5f) ,
		glm::vec2(0.8f, 0.2f)));
	mesh.vertices.push_back(Vertex(glm::vec3(0.0f, 255.0f, 0.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(0.5f, 0.5f, 0.5f) ,
		glm::vec2(0.7f, 0.4f)));
	mesh.vertices.push_back(Vertex(glm::vec3(15.0f, 0.0f, 0.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.6f, 0.2f)));


	mesh.vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec2(0.8f, 0.2f)));
	mesh.vertices.push_back(Vertex(glm::vec3(0.0f, 255.0f, 0.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec2(0.7f, 0.4f)));
	mesh.vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 15.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.6f, 0.2f)));*/
	Mutex.unlock();

}

bool Chunk::CheckIfSolidBlock(glm::vec3 Pos)
{
	return false;
}

void Chunk::UpdateMeshOnlyAdd(std::vector<Block>& BlocksToAdd)
{
	for (std::vector<Block>::iterator it = BlocksToAdd.begin(); it != BlocksToAdd.end(); ++it)
	{
		glm::vec3 Pos((ChunkPos.x * ChunkSize) + it->LocalPos.x,
			it->LocalPos.y,
			(ChunkPos.y * ChunkSize) + it->LocalPos.z);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 1.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace( mesh.GetVertexVector(), Faces::Up, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, -1.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.GetVertexVector(), Faces::Down, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 0.0f, 1.0f)) == nullptr) FaceBuilder::BuildFace( mesh.GetVertexVector(), Faces::North, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 0.0f, -1.0f)) == nullptr) FaceBuilder::BuildFace(mesh.GetVertexVector(), Faces::South, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(-1.0f, 0.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.GetVertexVector(), Faces::West, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(1.0f, 0.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace( mesh.GetVertexVector(), Faces::East, Pos, (BlockTypes)it->ID);


	}
}
void Chunk::UpdateMeshOnlyAddSingleBlock(Block block)
{
	glm::vec3 Pos((ChunkPos.x * ChunkSize) + block.LocalPos.x,
		block.LocalPos.y,
		(ChunkPos.y * ChunkSize) + block.LocalPos.z);
	if (vec3ToBlock(block.LocalPos + glm::vec3(0.0f, 1.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace( mesh.GetVertexVector(), Faces::Up, Pos, (BlockTypes)	6);
	if (vec3ToBlock(block.LocalPos + glm::vec3(0.0f, -1.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.GetVertexVector(), Faces::Down, Pos, (BlockTypes)	6);
	if (vec3ToBlock(block.LocalPos + glm::vec3(0.0f, 0.0f, 1.0f)) == nullptr) FaceBuilder::BuildFace( mesh.GetVertexVector(), Faces::North, Pos, (BlockTypes)	6);
	if (vec3ToBlock(block.LocalPos + glm::vec3(0.0f, 0.0f, -1.0f)) == nullptr) FaceBuilder::BuildFace(mesh.GetVertexVector(), Faces::South, Pos, (BlockTypes)6);
	if (vec3ToBlock(block.LocalPos + glm::vec3(-1.0f, 0.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.GetVertexVector(), Faces::West, Pos, (BlockTypes)	6);
	if (vec3ToBlock(block.LocalPos + glm::vec3(1.0f, 0.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace( mesh.GetVertexVector(), Faces::East, Pos, (BlockTypes)	6);


}

void Chunk::Draw(Shader& shader)
{
	if (Mutex.try_lock())
	{
		mesh.Draw(shader, glm::vec3(0, 0, 0));
		Mutex.unlock();
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

			chunkMenager->SetBlockInWorld(Util::LocPosAndChunkPosToWorldPos(LocPos, ChunkPos), Block(LocPos, ID));
			

			return false;


			glm::vec3 WorldPos = Util::LocPosAndChunkPosToWorldPos(LocPos,ChunkPos);
			glm::vec2 ChunkPos = Util::WorldPosToChunkPos(WorldPos);
			glm::vec3 LocalPos = Util::WorldPosToLocalPos(WorldPos);
			auto it = chunkMenager->BlockQueuesMap.find(ChunkPos);
			if (it != chunkMenager->BlockQueuesMap.end())
			{
				it->second.push_back(Block(LocalPos, BlockTypes::Dirt));
					//Add updating meshes to those chunks

			}
			else
			{
				std::vector<Block> b;
				b.push_back(Block(LocalPos, BlockTypes::Water));
				chunkMenager->BlockQueuesMap.emplace(std::make_pair<>(ChunkPos,b ));
	
			}
		}
	
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
		Blocks.insert(Blocks.end(), it->second.begin(), it->second.end());
		if (JustNewBlocks)	UpdateMeshOnlyAdd(it->second);
		else UpdateMesh();
	}
}

Block* Chunk::vec3ToBlock(glm::vec3 LocPos)
{
	auto search_result = block_map.find(LocPos);
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
