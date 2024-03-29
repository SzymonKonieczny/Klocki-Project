#pragma once
#ifndef UTIL_H
#define UTIL_H
#include <random>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "GLOBAL.h"
#include "BlockTypes.h"
#include "BlockTemplate.h"

class Util
{
	std::random_device rd;
	std::mt19937 gen;
	

	Util();
	static Util* Instance;

	public:
		static glm::vec2 WorldPosToChunkPos(glm::vec3 WorldPos);
		static glm::vec3 LocPosAndChunkPosToWorldPos(glm::vec3 LocPos, glm::vec2 ChunkPos);
		static glm::vec3 WorldPosToLocalPos(glm::vec3 WorldPos);
		static float lerp(float v0, float v1, float t);
		void LoadBlocks();
		static float LinearInterpolation(float p1, float p2, float t);
		static float BilinearInterpolation(float q11, float q12, float q21, float q22, glm::vec2 p1, glm::vec2 p2, glm::vec2 p);  //(float q11, float p12, float q21, float q22, float tx, float ty);

		

		Util(Util& other) = delete;
		void operator=(const Util&) = delete;
		static	Util* GetInstance();
	float random(int min, int max);
		std::vector<BlockTemplate> BLOCKS;
		
};


#endif // !UTIL_H
