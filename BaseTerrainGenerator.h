#pragma once
#include "ChunkMenager.h"
#include "Chunk.h"

#include <memory>
#include "SimplexNoise.h"

class BaseTerrainGenerator
{
	FastNoise::SmartNode<FastNoise::Simplex> fnSimplex;
	FastNoise::SmartNode<FastNoise::FractalFBm>  fnFractal;
	FastNoise::SmartNode<> fnGenerator;
	ChunkMenager* chunkmenager;
public:
	virtual void Generate(std::shared_ptr<Chunk> chunkptr);
	virtual void GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir = glm::vec3(0, 0, 1), int branches = 6);

	 BaseTerrainGenerator(ChunkMenager* menager);
	 ~BaseTerrainGenerator();
};