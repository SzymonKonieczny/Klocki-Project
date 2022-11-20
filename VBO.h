#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
#include<glm/glm.hpp>

#include <vector>

struct CompressedVertex
{
	unsigned int CompressedData1;
	//unsigned int CompressedData2;

}; 

struct UncompressedVertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texturePos;
};

template<typename T>
class VBO
{
public:

	GLuint ID;

	VBO(std::vector<T>& vertices)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);
	}


	void Bind() 
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Rebuffer(std::vector<T>& vertices)
	{

		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);

	}

	void Delete()
	{
		glDeleteBuffers(1, &ID);
	}
};

#endif