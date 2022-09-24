#pragma once
#include "Chunk.h"
#include <set>
class Renderer
{
	std::set<std::shared_ptr<Chunk>> ChunkSet; //(Optimization) potentially I could also store ChunkPos, and avoid copying shared pointers

public :
	Shader* ChunkShader;
	Shader* EntityShader;

	Texture* TextureAtlas;

	void AddToSet(std::shared_ptr<Chunk> ch);
	void DrawChunks();

};
