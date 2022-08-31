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
		void LoadBlocks();
		Util(Util& other) = delete;
		void operator=(const Util&) = delete;
		static	Util* GetInstance();
	float random(int min, int max);
		std::vector<BlockTemplate> BLOCKS;
		
};


#endif // !UTIL_H
