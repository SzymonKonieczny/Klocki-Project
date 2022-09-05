#include "World.h"


void World::AsyncGenerate(std::shared_ptr < std::vector< std::shared_ptr<Chunk>>> vec, bool* LastBatchReady)
{
	*LastBatchReady = false;


	for (int i = 0; i < vec->size(); i++)
	{
		(*vec)[i]->Generate(1);

		//terrainGenerator
	}
	vec->clear();
	*LastBatchReady = true;

}
void AsyncMesh(std::shared_ptr <std::vector<std::shared_ptr<Chunk>>> vec, bool* LastBatchReady, TerrainGenerator& tg)
{
	*LastBatchReady = false;


	for (int i = 0; i < vec->size(); i++)
	{
		//(*vec)[i]->Generate(1);
		tg.Generate((*vec)[i]);

		(*vec)[i]->UpdateMesh();
	}
	vec->clear();
	*LastBatchReady = true;

}
World::World() :chunkMenager(this), terrainGenerator(&chunkMenager)
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
			//GenChunkOnPosVec.push_back(s);
			
			
			//std::shared_ptr<Chunk> s;
			//s = it->second;
			GenChunkOnPosVec->push_back(it->second);
		}

	}
	std::thread f( AsyncMesh, GenChunkOnPosVec, &LastBatchReady, std::ref(terrainGenerator));
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
