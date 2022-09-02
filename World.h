#pragma once
#include<iostream>
#include<vector>
#include<glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <future>
#include <queue>
#include "Util.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"
#include"Camera.h"
#include "Window.h"
#include "ChunkMesh.h"
#include "GLOBAL.h"
#include "SimplexNoise.h"
#include "Player.h"
#include "Chunk.h"
#include "ChunkMenager.h"

class World
{

public:
	bool wasShaderSet=false;
	void SetShader(Shader* prog);
	World();
	Shader* shaderProgram;
	TerrainGenerator terrainGenerator;
	ChunkMenager chunkMenager;
	std::queue<glm::vec2> ChunkGenQueue;
	void NewChunk(glm::vec2 ChunkPos);
	void GenChunksFromQueue(int amount);
	void IdkWhatToCallThatForNow(Player& player);

};