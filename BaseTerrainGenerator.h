#pragma once
#include "ChunkMenager.h"
#include "Chunk.h"

#include <memory>
#include "SimplexNoise.h"

class BaseTerrainGenerator
{
public:
	FastNoise::SmartNode<FastNoise::Simplex> fnSimplex;
	FastNoise::SmartNode<FastNoise::FractalFBm>  fnFractal;
	FastNoise::SmartNode<> fnGenerator;
	ChunkMenager* chunkmenager;

	virtual void Generate(std::shared_ptr<Chunk> chunkptr)=0;
	virtual void GenerateTree(glm::vec3 WorldPos, glm::vec3 Dir = glm::vec3(0, 0, 1), int branches = 6)=0;

	 BaseTerrainGenerator(ChunkMenager* menager);

};