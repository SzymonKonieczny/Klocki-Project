#include "ChunkMenager.h"
#include "Chunk.h"
#include "World.h"
ChunkMenager::ChunkMenager(World* wrld)
{
	world = wrld;



}
void ChunkMenager::SpawnChunks()
{

	int Render = RenderDistance ;
	glm::vec2 CurrentPos = Util::WorldPosToChunkPos(glm::vec3(0));
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

	world->GenChunksFromQueue(Render * Render);


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

			auto it = ChunkMap.find(NewChunkPos);
			if (it == ChunkMap.end()) // if NOT in the world already
			{
				NewChunk(NewChunkPos);
				world->ChunkGenQueue.push(NewChunkPos);
			}

		}
		for (int i = -RenderDelete ; i <= RenderDelete; i++)
		{
			glm::vec2 DeleteChunkPos = (toDelete + CurrentCenter) + glm::vec2(Dir.y * i, Dir.x * i);//swap is important here AND CORRECT
			auto it = ChunkMap.find(DeleteChunkPos);
			if (it != ChunkMap.end())
			{
				ChunkMap.erase(DeleteChunkPos);

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
	auto existingChunksIterator = ChunkMap.find(ChunkPos);
	if (existingChunksIterator != ChunkMap.end())
	{
		existingChunksIterator->second->setblock(LocalPos, ID);
		//std::cout << "Adding to an existing chunk" << std::endl;
		existingChunksIterator->second->UpdateMeshOnlyAddSingleBlock(Block(LocalPos, ID));
		//existingChunksIterator->second.isDirty = true;

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

void ChunkMenager::NewChunk(glm::vec2 ChunkPos)
{


	ChunkMap.try_emplace(ChunkPos, std::make_shared<Chunk>(ChunkPos,this));
}
