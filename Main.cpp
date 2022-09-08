#include<iostream>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <future>


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
#include "BlockTemplate.h"
#include "Chunk.h"

#include "Game.h"

int main()
{
	



	std::cout << " Enter the seed and then the renderdistance " << std::endl;
	std::cin >> map_seed >> RenderDistance; 
	

	Game game;
/*	Mesh Orienterbackandup;
	Mesh Orienterfrontanddown;
	FaceBuilder::BuildFace(Orienterbackandup.GetVertexVector(), Faces::Up, glm::vec3(0, 0, 0));
	FaceBuilder::BuildFace(Orienterbackandup.GetVertexVector(), Faces::Down, glm::vec3(0, 0, 0));
	FaceBuilder::BuildFace(Orienterfrontanddown.GetVertexVector(), Faces::Up, glm::vec3(0, -1, -1));
	FaceBuilder::BuildFace(Orienterfrontanddown.GetVertexVector(), Faces::Down, glm::vec3(0, -1, -1));*/


	glm::mat4 Rotation = glm::mat4(1.0);
	Rotation = glm::rotate(Rotation, (1.0f/60) * 1/1 , glm::vec3(1.0, 1.0, 0.0));
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(Window::GetInstance()->window))
	{
		glClearColor(0.9f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		game.shaderProgram->Activate();
		
		//MeshC.model =  MeshC.model * Rotation;
		//camera.LookingAtDir = glm::vec3(Rotation * glm::vec4(camera.LookingAtDir, 1.0));
		//camera.Position += 0.01;

		game.tickEntities();
		game.WorldUpdate();
		//game.RenderChunksInFrustum();

		
		//Orienterbackandup.Draw(*game.shaderProgram, glm::vec3(0, 0, 0));
		//Orienterfrontanddown.Draw(*game.shaderProgram, glm::vec3(0, 0, 0));
		glfwSwapBuffers(Window::GetInstance()->window);
		glfwPollEvents();
	}



	return 0;
}
