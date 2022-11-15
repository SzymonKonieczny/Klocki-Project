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

	VBO(std::vector<T>& vertices);


	void Bind();

	void Unbind();

	void Rebuffer(std::vector<T>& vertices);

	void Delete();
};

#endif