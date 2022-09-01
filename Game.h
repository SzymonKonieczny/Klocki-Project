#pragma once
#include<iostream>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb/stb_image.h>
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
class Game {
public:
	Shader* shaderProgram;
	Texture* TextureAtlas;
	Texture* PlayerTxt;
	Player player;
	std::queue<glm::vec2> ChunkGenQueue;
	int FramesTillResetQueue = 800;

	std::unordered_map<glm::vec2, Chunk> World;
		Game();
		void ShaderAndTextureStuff();
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void RenderChunksInFrustum();
		void tickEntities();
		void DrawEntities();
		void GenChunksFromQueue(int amount);
		void ClearScreen();

private:
	void PlaygroundForExperiments();
	void HandleWorldLoadingPositionChangeBased();
	void HandleWorldLoadingDistanceBased();
};