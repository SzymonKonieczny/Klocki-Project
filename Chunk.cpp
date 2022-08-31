#include "Chunk.h"

Chunk::Chunk(glm::vec2 ChunkCoords)
{
	ChunkPos = ChunkCoords;
}

void Chunk::Generate(int height_)
{
	std::cout << "Generating chunk Pos:" << ChunkPos.x << ' ' << ChunkPos.y << std::endl;
	int height = height_;

	for (int i = 0; i < ChunkSize; i++) //i = X coordinate
	{


		for (int j = 0; j < ChunkSize; j++) // j = Z coordinate
		{
			for (int k = 0; k < height; k++) // k = Y coordinate
			{

				setblock(glm::vec3(i, k, j), 0);


			}


		}
	}
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
		if (vec3ToBlock(it->LocalPos +  glm::vec3(0.0f, 1.0f, 0.0f)) ==nullptr) BlockTemplate::BuildFace(mesh.vertices, Faces::Up, Pos);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, -1.0f, 0.0f)) == nullptr) BlockTemplate::BuildFace(mesh.vertices, Faces::Down, Pos);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 0.0f, 1.0f)) == nullptr) BlockTemplate::BuildFace(mesh.vertices, Faces::North, Pos);
		if (vec3ToBlock(it->LocalPos + glm::vec3(0.0f, 0.0f, -1.0f)) == nullptr) BlockTemplate::BuildFace(mesh.vertices, Faces::South, Pos);
		if (vec3ToBlock(it->LocalPos + glm::vec3(-1.0f, 0.0f, 0.0f)) == nullptr) BlockTemplate::BuildFace(mesh.vertices, Faces::West, Pos);
		if (vec3ToBlock(it->LocalPos + glm::vec3(1.0f, 0.0f, 0.0f)) == nullptr) BlockTemplate::BuildFace(mesh.vertices, Faces::East, Pos);


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
			std::cout << "Not a viable position. Block requested at " << LocPos.x << " " << LocPos.y + '\n';
			return false;
		}
	
		if (block_map.find(glm::vec3(LocPos.x, LocPos.y, LocPos.z)) != block_map.end())
		{
			Blocks[block_map[glm::vec3(LocPos.x, LocPos.y, LocPos.z)]].ID = ID;
		}
		else
		{
			//Blocks.push_back(ID);
			Blocks.push_back(Block{ glm::vec3(LocPos.x, LocPos.y, LocPos.z), ID }); //from terraria project
			block_map.insert(std::make_pair(glm::vec3(LocPos.x, LocPos.y, LocPos.z), Blocks.size() - 1));
		}


	return true;
}

bool Chunk::isPositionViable(glm::vec3 LocPos)
{
	return !(LocPos.x > ChunkSize - 1 || LocPos.x < 0 || LocPos.y < 0 || LocPos.y > ChunkHeight - 1 
		|| LocPos.z > ChunkSize - 1 || LocPos.z < 0);

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
