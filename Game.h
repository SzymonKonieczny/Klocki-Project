#pragma once
#include<iostream>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <queue>

#include "World.h" //has all the includes, idgaf 


class Game {
public:
	Shader* shaderProgram;
	Texture* TextureAtlas;
	Texture* PlayerTxt;
	Player player;
	World world;

		Game();
		void ShaderAndTextureStuff();
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void RenderChunksInFrustum();
		void tickEntities();
		void DrawEntities();
		void GenChunksFromQueue(int amount);
		void ClearScreen();
		void WorldUpdate();

private:
	void PlaygroundForExperiments();
	void HandleWorldLoadingPositionChangeBased();
	void HandleWorldLoadingDistanceBased();
	double crntTime;
	double timeDiff;
	int counter;
	double prevTime;
};