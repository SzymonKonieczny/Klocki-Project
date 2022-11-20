#pragma once
#ifndef MESH_H
#define	MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <mutex>

#include "shaderClass.h"
#include "VBO.h"
#include"VAO.h"
#include"EBO.h"
#include"Texture.h"
#include "Block.h"
#include "GLOBAL.h"
#include "Camera.h"


template <typename T>
class Mesh{
	std::vector<T> vertices;
	std::mutex VerticiesMutex;
public:
	
	glm::mat4 model = glm::mat4(1.0f);
	bool verticiesReady = false;

	bool mingledWith = false;
	std::vector < GLuint> indices;
	//Mesh(std::vector<Vertex>& vertices_, std::vector < GLuint>& indices_);
	Mesh() : VBO1(vertices)
	{
		// Generates Vertex Array Object and binds it

		//New
		//VAO.LinkAttrib(VBO1, 0, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*)0);

		//Old
		//VAO.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		//VAO.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		//VAO.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

		// Unbind all to prevent accidentally modifying them
		//EBO1->Unbind();

	}
	/*~Mesh()
	{

	}*/
	//void Generate(const std::vector<std::vector<Block>>& BlockColumns,const glm::ivec2 ChunkPos );
	
	VAO<T> VAO;
	VBO<T> VBO1;
	std::vector<T>& GetVertexVector()
	{
		mingledWith = true;
		return vertices;
	}
	void verticiesSetNotReady()
	{
		verticiesReady = false;
	}
	void verticiesSetReady()
	{
		verticiesReady = true;
	}
	virtual void LinkVBOAttributes()=0;
	void MarkDirty();
	void AddToVerticies(T vert)
	{
		VerticiesMutex.lock();
		mingledWith = true;
		vertices.push_back(vert);
		VerticiesMutex.unlock();
	};
	void ClearVerticies()
	{
		VerticiesMutex.lock();
		mingledWith = true;
		vertices.clear();
		VerticiesMutex.unlock();
	}


	void Draw(Shader& shader, glm::vec3 Position, bool UseModelMatrix = false)
	{
		if (mingledWith && verticiesReady)
		{
			VBO1.Rebuffer(vertices);
			glFinish();

			mingledWith = false;
		}
		VAO.Bind();
		if (UseModelMatrix)
		{
			//model = model * glm::translate(glm::vec3(Position));
			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(glm::translate(glm::vec3(Position))));
		}
		else glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		VAO.Unbind();

	}
};

#endif // !MESH_H
