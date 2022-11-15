#pragma once
#include<iostream>
#include<vector>
#include<glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <future>
#include <unordered_set>

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
#include <thread>
#include "CustomTerrainGenerator.h"
#include "FlatTerrainGenerator.h"
#include "Renderer.h"

class World
{
	bool LastGenMeshBatchReady = true;
	bool LastMeshBatchReady = true;
	std::shared_ptr<std::thread> MeshThread;
	std::thread* GenerationThread;
	std::queue<glm::vec2> ChunkMeshAddQueue;
	std::unordered_set<glm::vec2> ChunkMeshQMembers;
public:
	Renderer renderer;

	//void AsyncMesh(std::vector< std::unordered_map<glm::vec2, Chunk>::iterator> vec);
	bool wasShaderSet=false;
	void SetShader(Shader* prog);
	World(); 
	Shader* shaderProgram;
	TerrainGenerator terrainGenerator;
	ChunkMenager chunkMenager;
	std::queue<glm::vec2> ChunkGenQueue;



	void NewChunk(glm::vec2 ChunkPos);
	void GenChunksFromQueue(int amount);
	void AddChunksToGen(glm::vec2 ChunkPos);

	void MeshUpdateFromQueue(int amount);
	void AddChunksMeshToUpdate(glm::vec2 ChunkPos);

	void IdkWhatToCallThatForNow(Player& player, float dt);
	void AsyncGenerate(std::shared_ptr < std::vector< std::shared_ptr<Chunk>>> vec, bool* LastBatchReady);
	};