#include "World.h"


void AsyncMesh(std::shared_ptr < std::vector< std::shared_ptr<Chunk>>> vec, bool* LastBatchReady)
{
	*LastBatchReady = false;

	/*for (std::shared_ptr<Chunk> chunk : vec)
	{
		chunk->UpdateMesh();
	}*/
	for (int i = 0; i < vec->size(); i++)
	{
		(*vec)[i]->Generate(1);

		(*vec)[i]->UpdateMesh();
	}
	vec->clear();
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
	std::shared_ptr < std::vector< std::shared_ptr<Chunk>>> GenChunkOnPosVec = std::make_shared< std::vector< std::shared_ptr<Chunk>>>();
	for (int i = 0; i < amount; i++)
	{
		if (ChunkGenQueue.empty()) return;
		glm::vec2 GenChunkOnPos = ChunkGenQueue.front();
		
		ChunkGenQueue.pop();
		auto it = chunkMenager.ChunkMap.find(GenChunkOnPos);
		if (it != chunkMenager.ChunkMap.end())
		{
			//it->second->Generate(1);
			
			GenChunkOnPosVec->push_back(it->second);
			
			//std::shared_ptr<Chunk> s;
			//s = it->second;
			//GenChunkOnPosVec.push_back(s);
			//it->second->UpdateMesh();

		}

	}
	std::thread f( AsyncMesh, GenChunkOnPosVec, &LastBatchReady);
	f.detach();
	
}



void World::IdkWhatToCallThatForNow(Player& player)
{
	if (!wasShaderSet)
	{
		std::cout << "THE SHADER FOR THE WORLD HAS TO BE SET!!!!!!!!!!";
		return;
	}

	chunkMenager.HandleWorldLoadingPositionChangeBased(player);
	for (std::unordered_map<glm::vec2, std::shared_ptr<Chunk>>::iterator it = chunkMenager.ChunkMap.begin(); it != chunkMenager.ChunkMap.end(); it++)
	{
		if(glm::distance(Util::WorldPosToChunkPos(player.Position),it->first) < RenderDistance)
		it->second->Draw(*shaderProgram);
	}

	GenChunksFromQueue(5);

}
