#include "ChunkMenager.h"
#include "Chunk.h"
#include "World.h"
ChunkMenager::ChunkMenager(World* wrld)
{
	world = wrld;



}
void ChunkMenager::SpawnChunks()
{
	glm::vec2 CurrentPos = Util::WorldPosToChunkPos(glm::vec3(0));
	for (int i = -RenderDistance *2 ; i <= RenderDistance*2 ; i++)
	{

		for (int k = -RenderDistance*2 ; k <= RenderDistance*2 ; k++)
		{
			glm::vec2 ChunkPos = glm::vec2(i, k) + CurrentPos;
			NewChunk(ChunkPos);
			world->ChunkGenQueue.push(ChunkPos);
		}
	}
	std::cout << "Spawn is generating..." << std::endl;

	world->GenChunksFromQueue(RenderDistance * 8);
}
void ChunkMenager::HandleWorldLoadingPositionChangeBased(Player& player)
{
	if (FramesTillResetQueue <= 0)
	{
		// BlockQueuesMap.clear();
		FramesTillResetQueue = 1000;
		std::cout << "Clearing the Q cycle (currently disabled)" << std::endl;
	}
	FramesTillResetQueue--;


	if (player.LastFrameChunkPos != Util::GetInstance()->WorldPosToChunkPos(player.Position))
	{
		glm::vec2 Dir = Util::GetInstance()->WorldPosToChunkPos(player.Position) - player.LastFrameChunkPos;
		glm::vec2 toGenerate = glm::vec2(Dir.x * RenderDistance, Dir.y * RenderDistance);
		glm::vec2 toDelete = -glm::vec2(Dir.x * RenderDistance * 2, Dir.y * RenderDistance * 2) - Dir;
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
		for (int i = -RenderDistance * 2; i <= RenderDistance * 2; i++)
		{
			glm::vec2 DeleteChunkPos = (toDelete + CurrentCenter) + glm::vec2(Dir.y * i, Dir.x * i);//swap is important here AND CORRECT
			auto it = ChunkMap.find(DeleteChunkPos);
			if (it != ChunkMap.end())
			{
				ChunkMap.erase(DeleteChunkPos);

			}
		}


		player.LastFrameChunkPos = CurrentCenter;

	}
}

void ChunkMenager::SetBlockInWorld(glm::vec3 WorldPos, Block block)
{
	glm::vec2 ChunkPos = Util::WorldPosToChunkPos(WorldPos);
	glm::vec3 LocalPos = Util::WorldPosToLocalPos(WorldPos);
	auto existingChunksIterator = ChunkMap.find(ChunkPos);
	if (existingChunksIterator != ChunkMap.end())
	{
		existingChunksIterator->second.setblock(LocalPos, block.ID);
		//std::cout << "Adding to an existing chunk" << std::endl;
		existingChunksIterator->second.UpdateMeshOnlyAddSingleBlock(Block(LocalPos, block.ID));
		//existingChunksIterator->second.isDirty = true;

	}
	else
	{


		auto it = BlockQueuesMap.find(ChunkPos);
		if (it != BlockQueuesMap.end())
		{
			
			it->second.push_back(Block(LocalPos, BlockTypes::Dirt));
			
		}
		else
		{
			std::vector<Block> b;
			b.push_back(Block(LocalPos, BlockTypes::Water));
			BlockQueuesMap.emplace(std::make_pair<>(ChunkPos, b));

		}
	}


}

void ChunkMenager::NewChunk(glm::vec2 ChunkPos)
{
	ChunkMap.try_emplace(ChunkPos, ChunkPos, this);
}
