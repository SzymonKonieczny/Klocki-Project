#include "Chunk.h"
std::unordered_map<glm::vec2, std::vector<Block>> Chunk::BlockQueuesMap = std::unordered_map<glm::vec2, std::vector<Block>>();
Chunk::Chunk(glm::vec2 ChunkCoords)
{
	ChunkPos = ChunkCoords;
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
					if (Util::GetInstance()->random(0, 100) < 2) GenerateTree(glm::vec3(j, k, i));
					else setblock(glm::vec3(j, k, i), BlockTypes::Grass);
					
					
				
				}
				else setblock(glm::vec3(j, k, i), BlockTypes::Stone);
				
				//setblock(glm::vec3(j, k, i), Util::GetInstance()->random(0,9));
			}


		}
	}
	UpdateBlocksFromBlockQueueMap(false);
	
}

void Chunk::UpdateMesh()
{
	mesh.vertices.clear();
	//for (int i = 0; i < Blocks.size(); i++)

	for (std::vector<Block>::iterator it = Blocks.begin(); it != Blocks.end(); ++it)
	{
		glm::vec3 Pos((ChunkPos.x*ChunkSize) + it->LocalPos.x, 
			 it->LocalPos.y,
			(ChunkPos.y * ChunkSize) + it->LocalPos.z);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 1.0f, 0.0f)) == nullptr) FaceBuilder ::BuildFace(mesh.vertices, Faces::Up, Pos,(BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, -1.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::Down, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 0.0f, 1.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::North, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 0.0f, -1.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::South, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(-1.0f, 0.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::West, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(1.0f, 0.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::East, Pos, (BlockTypes)it->ID);


	}
	/*glm::vec3(0.0f, 0.0, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0, 1)*/
	mesh.vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(0.5f, 0.5f, 0.5f) ,
		glm::vec2(0, 0)));
	mesh.vertices.push_back(Vertex(glm::vec3(0.0f, 255.0f, 0.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(0.5f, 0.5f, 0.5f) ,
		glm::vec2(0, 0)));
	mesh.vertices.push_back(Vertex(glm::vec3(1.0f, 0.0f, 0.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0, 0)));


	mesh.vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec2(0, 0)));
	mesh.vertices.push_back(Vertex(glm::vec3(0.0f, 255.0f, 0.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec2(0, 0)));
	mesh.vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 1.0f) + glm::vec3(ChunkPos.x * ChunkSize, 0, ChunkPos.y * ChunkSize),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0, 0)));
}

void Chunk::UpdateMeshOnlyAdd(std::vector<Block>& BlocksToAdd)
{
	for (std::vector<Block>::iterator it = BlocksToAdd.begin(); it != BlocksToAdd.end(); ++it)
	{
		glm::vec3 Pos((ChunkPos.x * ChunkSize) + it->LocalPos.x,
			it->LocalPos.y,
			(ChunkPos.y * ChunkSize) + it->LocalPos.z);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 1.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::Up, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, -1.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::Down, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 0.0f, 1.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::North, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 0.0f, -1.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::South, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(-1.0f, 0.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::West, Pos, (BlockTypes)it->ID);
		if (vec3ToBlock(it->LocalPos + glm::vec3(1.0f, 0.0f, 0.0f)) == nullptr) FaceBuilder::BuildFace(mesh.vertices, Faces::East, Pos, (BlockTypes)it->ID);


	}
}

void Chunk::Draw(Shader& shader)
{
	mesh.Draw(shader, glm::vec3(0,0,0));
}

	

	bool Chunk::setblock(glm::vec3 LocPos, int ID)
{// returns true if the placement was succesful
		if (!isPositionViable(LocPos))
		{
			//std::cout << "Not a viable position. Block requested at " << LocPos.x << " " << LocPos.y + '\n';
			glm::vec3 WorldPos = glm::vec3(LocPos.x + ChunkPos.x * ChunkSize, LocPos.y, LocPos.z + ChunkPos.y /*<- because chunkPos is a vec2*/ * ChunkSize);
			glm::vec2 ChunkPos = Util::WorldPosToChunkPos(WorldPos);
			glm::vec3 LocalPos = glm::vec3(WorldPos.x - ChunkPos.x * ChunkSize, WorldPos.y, WorldPos.z - ChunkPos.y * ChunkSize);
			auto it = Chunk::BlockQueuesMap.find(WorldPos);
			if (it != Chunk::BlockQueuesMap.end())
			{
				it->second.push_back(Block(LocalPos,ID));
					//Add updating meshes to those chunks

			}
			else
			{
				std::vector<Block> b;
				b.push_back(Block(LocalPos, ID));
				Chunk::BlockQueuesMap.emplace(std::make_pair<>(ChunkPos,b ));

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



	void Chunk::GenerateTree(glm::vec3 LocPos)
	{
		glm::vec3 Up(0, 1, 0);
		glm::vec3 North(0, 0, 1);
		setblock(LocPos+Up+North, 4);
		for (int i = 0; i < 4; i++)
		{
			LocPos += Up + North;
			setblock(LocPos , 4);
		}
		for (int i = 0; i < 3; i++)
		{
			LocPos += Up;
			setblock(LocPos, 4);
		}



	}


	bool Chunk::isPositionViable(glm::vec3 LocPos)
{
	return !(LocPos.x > ChunkSize - 1 || LocPos.x < 0 || LocPos.y < 0 || LocPos.y > ChunkHeight - 1 
		|| LocPos.z > ChunkSize - 1 || LocPos.z < 0);

}

void Chunk::UpdateBlocksFromBlockQueueMap(bool JustNewBlocks)
{
	auto it = BlockQueuesMap.find(ChunkPos);
	if (it != BlockQueuesMap.end())
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
