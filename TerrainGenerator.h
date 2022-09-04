#pragma once
#include "Chunk.h"
#include "SimplexNoise.h"

class TerrainGenerator
{

	void Generate(std::shared_ptr<Chunk> chunkptr);
	public:
	TerrainGenerator();
	~TerrainGenerator();
};