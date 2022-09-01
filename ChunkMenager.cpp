#include "ChunkMenager.h"
#include "Chunk.h"
void ChunkMenager::HandleWorldLoadingPositionChangeBased()
{

}

void ChunkMenager::SetBlock(glm::vec3 WorldPos, Block block)
{
	glm::vec2 ChunkPos = Util::WorldPosToChunkPos(WorldPos);
	glm::vec3 LocalPos = glm::vec3();
	auto it = ChunkMap.find(ChunkPos);
	if (it != ChunkMap.end())
	{
		it->second.setblock(LocalPos, block.ID);

	}
	else
	{
		std::vector<Block> b;
		b.push_back(Block(LocalPos, block.ID));
		BlockQueuesMap.emplace(std::make_pair<>(ChunkPos, b));

	}
}

void ChunkMenager::NewChunk(glm::vec2 ChunkPos)
{
	ChunkMap.emplace(std::make_pair<>(ChunkPos, Chunk(ChunkPos, this)));
}
