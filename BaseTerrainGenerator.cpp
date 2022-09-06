#include "BaseTerrainGenerator.h"
BaseTerrainGenerator::BaseTerrainGenerator(ChunkMenager* menager) : chunkmenager(menager)
{
	fnSimplex = FastNoise::New<FastNoise::Simplex>();
	fnFractal = FastNoise::New<FastNoise::FractalFBm>();

	fnFractal->SetSource(fnSimplex);
	fnFractal->SetOctaveCount(5);

}