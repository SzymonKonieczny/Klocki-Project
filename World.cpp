#include "World.h"


void World::AsyncGenerate(std::shared_ptr < std::vector< std::shared_ptr<Chunk>>> vec, bool* LastBatchReady)
{
	return;

	//UNUSED
	// 
	// 



	for (int i = 0; i < vec->size(); i++)
	{
		(*vec)[i]->Generate(1);

		//terrainGenerator
	}
	vec->clear();
	*LastBatchReady = true;

}
void AsyncGenerateAndMesh(std::shared_ptr <std::vector<std::shared_ptr<Chunk>>> vec, bool& LastBatchReady, BaseTerrainGenerator* tg)
{
//	LastBatchReady = false;


	for (int i = 0; i < vec->size(); i++)
	{
		//(*vec)[i]->Generate(1);
	//	std::cout << "Generating chunk Pos:" << (*vec)[i]->ChunkPos.x << ' ' << (*vec)[i]->ChunkPos.y << std::endl;

		tg->Generate((*vec)[i]);
		
	//	(*vec)[i]->UpdateMesh();
	}
	vec->clear();
	LastBatchReady = true;

}
void AsyncMeshOnly(std::shared_ptr <std::vector<std::shared_ptr<Chunk>>> vec, bool& LastBatchReady)
{
	//LastBatchReady = false; Done before invoking the thread


	for (int i = 0; i < vec->size(); i++)
	{
		//std::cout << "Meshing chunk Pos:" << (*vec)[i]->ChunkPos.x << ' ' << (*vec)[i]->ChunkPos.y << std::endl;
		(*vec)[i]->UpdateMesh();
	}
	vec->clear();
	LastBatchReady = true;


}
World::World() :chunkMenager(this), terrainGenerator(&chunkMenager),entityMenager(this)
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
	static glm::vec2 LastChunkPos = glm::vec2(69,6999);
	if (!LastGenMeshBatchReady)
	{
		//std::cout << "Stil Generating : "<<LastChunkPos.x << ' '<<LastChunkPos.y<<" last batch NOT ready \n";

		return;
	}
	std::shared_ptr < std::vector< std::shared_ptr<Chunk>>> GenChunkOnPosVec = std::make_shared< std::vector< std::shared_ptr<Chunk>>>();
	for (int i = 0; i < amount; i++)
	{
		if (ChunkGenQueue.empty()) {
			//std::cout << "Generating Q empty, last batch ready \n";
			return;
		}
		glm::vec2 GenChunkOnPos = ChunkGenQueue.front();
		
		ChunkGenQueue.pop();
		auto it = chunkMenager.ChunkMap.find(GenChunkOnPos);
		if (it != chunkMenager.ChunkMap.end())
		{
			//it->second->Generate(1);
			//GenChunkOnPosVec.push_back(s);
			
			
			std::shared_ptr<Chunk> s= it->second;
			GenChunkOnPosVec->push_back(s);
			LastChunkPos = it->second->ChunkPos;
			//GenChunkOnPosVec->push_back(it->second);
		}

	}
	LastGenMeshBatchReady = false;
	std::thread f(AsyncGenerateAndMesh, GenChunkOnPosVec, std::ref(LastGenMeshBatchReady), (BaseTerrainGenerator*)&terrainGenerator);

	f.detach();

	
}

void World::AddChunksToGen(glm::vec2 ChunkPos)
{

	ChunkGenQueue.push(ChunkPos);

}

void World::MeshUpdateFromQueue(int amount)
{
	static glm::vec2 LastChunkPos = glm::vec2(69, 6999);
	if (!LastMeshBatchReady)
	{
		//std::cout << "Meshing :  last batch NOT ready \n";
		//std::cout << "Stil Meshing : " << LastChunkPos.x << ' ' << LastChunkPos.y << " last batch NOT ready \n";

		return;
	}
	std::shared_ptr < std::vector< std::shared_ptr<Chunk>>> UpdateChunkMeshOnPosVec = std::make_shared< std::vector< std::shared_ptr<Chunk>>>();
	for (int i = 0; i < amount; i++)
	{

		if (ChunkMeshAddQueue.empty()) {

			//	std::cout << "Meshing Q empty, last batch ready \n";
			continue;
		}
		glm::vec2 GenChunkOnPos = ChunkMeshAddQueue.front();

		ChunkMeshAddQueue.pop();
		ChunkMeshQMembers.erase(GenChunkOnPos);

		auto it = chunkMenager.ChunkMap.find(GenChunkOnPos);
		if (it != chunkMenager.ChunkMap.end())
		{
			//it->second->Generate(1);
			//GenChunkOnPosVec.push_back(s);


			std::shared_ptr<Chunk> s = it->second;
			UpdateChunkMeshOnPosVec->push_back(s);
			LastChunkPos = s->ChunkPos;
			//GenChunkOnPosVec->push_back(it->second);
		}

	}
	if (UpdateChunkMeshOnPosVec->empty()) return;
	if (MeshThread == nullptr)
	{
		LastMeshBatchReady = false;
		MeshThread = std::make_shared< std::thread>(AsyncMeshOnly, UpdateChunkMeshOnPosVec, std::ref(LastMeshBatchReady));
		MeshThread->detach();
	}
	if ( LastMeshBatchReady&& MeshThread != nullptr)
	{

		LastMeshBatchReady = false;
		MeshThread = std::make_shared< std::thread>(AsyncMeshOnly, UpdateChunkMeshOnPosVec, std::ref(LastMeshBatchReady));
		MeshThread->detach();
	}
}
void World::AddChunksMeshToUpdate(glm::vec2 ChunkPos)
{	
	if (!ChunkMeshQMembers.contains(ChunkPos))
	{
		ChunkMeshQMembers.emplace(ChunkPos);
		ChunkMeshAddQueue.push(ChunkPos); 
	}

}



void World::IdkWhatToCallThatForNow(Player& player, float dt)
{
	if (!wasShaderSet)
	{
		std::cout << "THE SHADER FOR THE WORLD HAS TO BE SET!!!!!!!!!!";
		return;
	}

	chunkMenager.HandleWorldLoadingPositionChangeBased(player);
	for (std::unordered_map<glm::vec2, std::shared_ptr<Chunk>>::iterator it = chunkMenager.ChunkMap.begin(); it != chunkMenager.ChunkMap.end(); it++)
	{
		if (glm::distance(Util::WorldPosToChunkPos(player.Position), it->first) < RenderDistance)
			renderer.AddToChunkSet(it->second);
	}
	for (std::unordered_map<unsigned int, std::shared_ptr<Entity>>::iterator it = entityMenager.EntityMap.begin(); it != entityMenager.EntityMap.end(); it++)
	{
	//	if (glm::distance(player.Position, it->second->Position) < RenderDistance/2)
			renderer.AddToEntitiesSet(it->second);
	}

	renderer.DrawChunks(&player.Cam);
	GenChunksFromQueue(1);
	MeshUpdateFromQueue(5);

}
