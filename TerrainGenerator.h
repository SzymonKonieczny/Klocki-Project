#pragma once
#include <memory>
#include "Chunk.h"
#include "SimplexNoise.h"

class TerrainGenerator
{

	public:
	void Generate(std::shared_ptr<Chunk> chunkptr);

	TerrainGenerator();
	~TerrainGenerator();
};