#include "World.h"


void AsyncMesh(std::vector< Chunk*>& vec, bool* LastBatchReady)
{
	*LastBatchReady = false;

	for (Chunk* chunk : vec)
	{
		chunk->UpdateMesh();
	}
	*LastBatchReady = true;

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

	if (!LastBatchReady) 
		return;
	std::vector< Chunk*> GenChunkOnPosVec;
	for (int i = 0; i < amount; i++)
	{
		if (ChunkGenQueue.empty()) return;
		glm::vec2 GenChunkOnPos = ChunkGenQueue.front();
		
		ChunkGenQueue.pop();
		auto it = chunkMenager.ChunkMap.find(GenChunkOnPos);
		if (it != chunkMenager.ChunkMap.end())
		{
			it->second.Generate(1);

			GenChunkOnPosVec.push_back(&it->second);
	
			it->second.UpdateMesh();

		}

	}
	//std::thread f( AsyncMesh, std::ref(GenChunkOnPosVec), &LastBatchReady);
	//f.detach();
	
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

	GenChunksFromQueue(5);

}
