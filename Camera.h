#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "shaderClass.h"
#include "Window.h"
class Camera
{
	int modelLoc;
		
	int viewLoc;
		
	int projLoc;

	int TranslucentmodelLoc;

	int TranslucentviewLoc;

	int TranslucentprojLoc;

	int EntitymodelLoc;

	int EntityviewLoc;

	int EntityprojLoc;

public:
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 view = glm::mat4(1.0);		//The Camera
	glm::mat4 proj = glm::mat4(1.0);
	


	glm::vec3 Position;
	glm::vec3 LookingAtDir = glm::vec3(0.0f, 0.0f, -1.0f);
	Camera(glm::vec3 position);
	void UpdateView();

	void GetUniformLocations(Shader& shaderProgram);

	void UpdateUniformsTransparent();

	void UpdateUniformsEntity();

	void GetUniformLocationsForTransparent(Shader& shaderProgram);

	void GetUniformLocationsForEntity(Shader& shaderProgram);

	int GetModelUniformLocation();


};
