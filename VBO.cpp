#include"VBO.h"
template <typename T>

VBO<T>::VBO(std::vector<T>& vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);
}

template <typename T>

void VBO<T>::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
template <typename T>

void VBO<T>::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
template <typename T>

void VBO<T>::Rebuffer(std::vector<T>& vertices)
{

	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);

}

// Deletes the VBO
template <typename T>

void VBO<T>::Delete()
{
	glDeleteBuffers(1, &ID);
}