#include "World.h"


void AsyncMesh(std::vector< std::unordered_map<glm::vec2, Chunk>::iterator> vec)
{
	for (std::unordered_map<glm::vec2, Chunk>::iterator it : vec)
	{
		it->second.UpdateMesh();
	}
}
World::World() :chunkMenager(this)
{
	
}

void World::SetShader(Shader* prog)
{
	shaderProgram = prog;
	wasShaderSet = true;
}

void World::NewChunk(glm::vec2 ChunkPos)
{
	chunkMenager.NewChunk(ChunkPos);
}

void World::GenChunksFromQueue(int amount)
{
	std::vector< std::unordered_map<glm::vec2, Chunk>::iterator> GenChunkOnPosVec;
	for (int i = 0; i < amount; i++)
	{
		if (ChunkGenQueue.empty()) return;
		glm::vec2 GenChunkOnPos = ChunkGenQueue.front();
		
		ChunkGenQueue.pop();
		auto it = chunkMenager.ChunkMap.find(GenChunkOnPos);
		if (it != chunkMenager.ChunkMap.end())
		{
			it->second.Generate(1);

			GenChunkOnPosVec.push_back(it);
	
			//it->second.UpdateMesh();

		}

	}
	
	auto fut = std::async(std::launch::async, AsyncMesh, GenChunkOnPosVec);

}



void World::IdkWhatToCallThatForNow(Player& player)
{
	if (!wasShaderSet)
	{
		std::cout << "THE SHADER FOR THE WORLD HAS TO BE SET!!!!!!!!!!";
		return;
	}

	chunkMenager.HandleWorldLoadingPositionChangeBased(player);
	for (std::unordered_map<glm::vec2, Chunk>::iterator it = chunkMenager.ChunkMap.begin(); it != chunkMenager.ChunkMap.end(); it++)
	{
		it->second.Draw(*shaderProgram);
	}

	GenChunksFromQueue(1);

}
