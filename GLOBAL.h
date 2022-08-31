#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

#include <random>
#include <vector>
#include <FastNoise/FastNoise.h>
#include "Util.h"
#include "BlockTemplate.h"
#include "SimplexNoise.h"
extern const int ChunkSize;
extern const SimplexNoise MainNoise;
extern const int ChunkHeight;
extern const int WATERLEVEL;
extern const float texturedimention;
extern const int amoutOfBlocks;
extern int map_seed;


float random(int min, int max);



#endif // !GLOBAL_H

