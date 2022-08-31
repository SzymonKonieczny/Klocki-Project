#include"GLOBAL.h"

const int ChunkSize = 16;
const int WATERLEVEL = 50;
const int ChunkHeight = 256;
const SimplexNoise MainNoise;
int map_seed = 0;


const float texturedimention = 0.2f;
const int amoutOfBlocks = 10; // actual amount  +1


// std::vector<BlockTemplate> BLOCKS;
float random(int min, int max)
{

	return Util::GetInstance()->random(min, max);
	
}