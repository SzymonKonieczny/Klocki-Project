#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"
template <typename T>
class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO()
	{
		glGenVertexArrays(1, &ID);
	}

	// Links a VBO to the VAO using a certain layout
	void LinkAttrib(VBO<T>& VBO, GLuint layout,GLuint numComponents, GLenum type, GLsizeiptr stride , void* offset, bool UseIntAttribs)
	{
		Bind();
		VBO.Bind();
		if(UseIntAttribs)glVertexAttribIPointer(layout, numComponents, type, stride, offset);
		else glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		
		//glVertexAttribIPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		//glEnableVertexAttribArray(layout);
		glEnableVertexAttribArray(layout);

		Unbind();

		VBO.Unbind();
	}
	// Binds the VAO
	void Bind() 
	{
		glBindVertexArray(ID);
	}



	// Unbinds the VAO
	void Unbind() 
	{
		glBindVertexArray(0);
	}
	// Deletes the VAO
	void Delete()
	{
		glDeleteVertexArrays(1, &ID);
	}
};
#endif