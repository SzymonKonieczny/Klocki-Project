#pragma once

class ChunkMenager
{
public:
	std::unordered_map<glm::vec2, Chunk> ChunkList;
	void HandleWorldLoadingPositionChangeBased();
	void HandleWorldLoadingDistanceBased();
};