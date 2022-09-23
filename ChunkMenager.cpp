#include "ChunkMenager.h"
#include "Chunk.h"
#include "World.h"
ChunkMenager::ChunkMenager(World* wrld)
{
	world = wrld;



}
void ChunkMenager::SpawnChunks(glm::vec3 PlayerPos)
{

	int Render = RenderDistance ;
	glm::vec2 CurrentPos = Util::WorldPosToChunkPos(PlayerPos);
	for (int i = -Render ; i <= Render ; i++)
	{

		for (int k = -Render  ; k <= Render  ; k++)
		{
			glm::vec2 ChunkPos = glm::vec2(i, k) + CurrentPos;
			NewChunk(ChunkPos);
			world->ChunkGenQueue.push(ChunkPos);
		}
	}
	std::cout << "Spawn is generating..." << std::endl;

	world->GenChunksFromQueue(5);


}
void ChunkMenager::HandleWorldLoadingPositionChangeBased(Player& player)
{
	


	if (player.LastFrameChunkPos != Util::GetInstance()->WorldPosToChunkPos(player.Position))
	{

		int RenderDelete = RenderDistance *2;

		glm::vec2 Dir = Util::GetInstance()->WorldPosToChunkPos(player.Position) - player.LastFrameChunkPos;
		glm::vec2 toGenerate = glm::vec2(Dir.x * RenderDistance, Dir.y * RenderDistance);
		glm::vec2 toDelete = -glm::vec2(Dir.x * RenderDelete, Dir.y * RenderDelete) - Dir;
		glm::vec2 CurrentCenter = Util::GetInstance()->WorldPosToChunkPos(player.Position);
		for (int i = -RenderDistance; i <= RenderDistance; i++)
		{
			glm::vec2 NewChunkPos = (toGenerate + CurrentCenter) + glm::vec2(Dir.y * i, Dir.x * i);//swap is important here AND CORRECT

			auto it = GetChunkAt(NewChunkPos);	//	ChunkMap.find(NewChunkPos);
			if (it == nullptr) // if NOT in the world already
			{
				NewChunk(NewChunkPos);
				//world->ChunkGenQueue.push(NewChunkPos);
				world->AddChunksToGen(NewChunkPos);
			}

		}
		for (int i = -RenderDelete ; i <= RenderDelete; i++)
		{
			glm::vec2 DeleteChunkPos = (toDelete + CurrentCenter) + glm::vec2(Dir.y * i, Dir.x * i);//swap is important here AND CORRECT
			auto it = GetChunkAt(DeleteChunkPos); // ChunkMap.find(DeleteChunkPos);
			if (it != nullptr)
			{
				//ChunkMap.erase(DeleteChunkPos);
				EraseChunkAt(DeleteChunkPos);
			}
		}

		std::cout << ChunkMap.size() << "Chunks Currently Loaded \n";
		player.LastFrameChunkPos = CurrentCenter;

	}
}

void ChunkMenager::SetBlockInWorld(glm::vec3 WorldPos, int ID) 
{
	glm::vec2 ChunkPos = Util::WorldPosToChunkPos(WorldPos);
	glm::vec3 LocalPos = Util::WorldPosToLocalPos(WorldPos);
	SetBlockInWorld(LocalPos, ChunkPos, ID);
	return;
	/*auto existingChunksIterator = ChunkMap.find(ChunkPos);
	if (existingChunksIterator != ChunkMap.end())
	{
		existingChunksIterator->second->setblock(LocalPos, block.ID);
		//std::cout << "Adding to an existing chunk" << std::endl;
		existingChunksIterator->second->UpdateMeshOnlyAddSingleBlock(Block(LocalPos, block.ID));
		//existingChunksIterator->second.isDirty = true;

	}
	else
	{


		auto it = BlockQueuesMap.find(ChunkPos);
		if (it != BlockQueuesMap.end())
		{
			
			//it->second.push_back(Block(LocalPos, BlockTypes::Dirt));
			it->second.push_back(Block(LocalPos, block.ID));
			
		}
		else
		{
			std::vector<Block> b;
		//	b.push_back(Block(LocalPos, BlockTypes::Water));
			b.push_back(Block(LocalPos, block.ID));
			BlockQueuesMap.emplace(std::make_pair<>(ChunkPos, b));

		}
	}
	*/

}

void ChunkMenager::SetBlockInWorld(glm::vec3 LocalPos, glm::vec2 ChunkPos, int ID)
{
	//auto existingChunksIterator = ChunkMap.find(ChunkPos);
	auto existingChunksIterator = GetChunkAt(ChunkPos);
	if (existingChunksIterator != nullptr)
	{
		//existingChunksIterator->second->setblock(LocalPos, ID);
		existingChunksIterator->setblock(LocalPos, ID);


		//std::cout << "Adding to an existing chunk" << std::endl;
		//existingChunksIterator->second->UpdateMeshOnlyAddSingleBlock(Block(LocalPos, ID));
	//	existingChunksIterator->second->UpdateMesh();
		world->AddChunksMeshToUpdate(ChunkPos);
		//existingChunksIterator->second.setDirty();

	}
	else
	{


		auto it = BlockQueuesMap.find(ChunkPos);
		if (it != BlockQueuesMap.end())
		{

			//it->second.push_back(Block(LocalPos, BlockTypes::Dirt));
			it->second.push_back(Block(LocalPos, ID));

		}
		else
		{
			std::vector<Block> b;
			//	b.push_back(Block(LocalPos, BlockTypes::Water));
			b.push_back(Block(LocalPos, ID));
			BlockQueuesMap.emplace(std::make_pair<>(ChunkPos, b));

		}
	}
}

std::shared_ptr<Chunk> ChunkMenager::GetChunkAt(glm::vec2 ChunkPos)
{  
	std::shared_ptr<Chunk> ret;
	WorldMapMutex.lock();
	auto ptr =  ChunkMap.find(ChunkPos);
	if (ptr == ChunkMap.end()) ret = nullptr;
	else ret = ptr->second;
	WorldMapMutex.unlock();
	return ret;
}

void ChunkMenager::EraseChunkAt(glm::vec2 ChunkPos)
{
	WorldMapMutex.lock();
	ChunkMap.erase(ChunkPos);
	WorldMapMutex.unlock();

}

Block* ChunkMenager::GetBlockInWorld(glm::vec3 WorldPos )
{
	glm::vec2 ChunkPos = Util::WorldPosToChunkPos(WorldPos);
	glm::vec3 LocalPos = Util::WorldPosToLocalPos(WorldPos);
	return 	GetBlockInWorld(LocalPos, ChunkPos);
}

Block* ChunkMenager::GetBlockInWorld(glm::vec3 LocalPos, glm::vec2 ChunkPos)
{
	//auto existingChunksIterator = ChunkMap.find(ChunkPos);
	auto existingChunksIterator = GetChunkAt(ChunkPos);

	if (existingChunksIterator != nullptr)
	{
		return existingChunksIterator->vec3ToBlock(LocalPos);

	}
}

void ChunkMenager::NewChunk(glm::vec2 ChunkPos)
{

	WorldMapMutex.lock();
	ChunkMap.try_emplace(ChunkPos, std::make_shared<Chunk>(ChunkPos,this));
	WorldMapMutex.unlock();

}
