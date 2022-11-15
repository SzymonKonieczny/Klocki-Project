#include"VAO.h"

// Constructor that generates a VAO ID
template <typename T>
VAO<T>::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
template <typename T>
void VAO<T>::LinkAttrib(VBO<T>& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	Bind();
	VBO.Bind();
	glVertexAttribIPointer(layout, numComponents, type, stride, offset);
	//glVertexAttribIPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	//glEnableVertexAttribArray(layout);
	glEnableVertexAttribArray(layout);

	Unbind();

	VBO.Unbind();
}

// Binds the VAO
template <typename T>
void VAO<T>::Bind()
{
	glBindVertexArray(ID);
}



// Unbinds the VAO
template <typename T>
void VAO<T>::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
template <typename T>
void VAO<T>::Delete()
{
	glDeleteVertexArrays(1, &ID);
}