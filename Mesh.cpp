#include "Mesh.h"
/*

template<typename T>
Mesh<T>::Mesh(): VBO1(vertices)
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

template<typename T>
Mesh<T>::~Mesh()
{

}
template<typename T>
void  Mesh<T>::Draw(Shader& shader, glm::vec3 Position, bool UseModelMatrix)  {


	//shader.Activate(); UNUSED. CAN DELETE


	if (mingledWith && verticiesReady)
	{
		VBO1.Rebuffer(vertices);
		//EBO1->Rebuffer(indices);
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

	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	VAO.Unbind();

}
template<typename T>
std::vector<T>& Mesh<T>::GetVertexVector()
{
	mingledWith = true;
	return vertices;
}
template<typename T>
void Mesh<T>::verticiesSetNotReady()
{
	verticiesReady = false;
}
template<typename T>
void  Mesh<T>::verticiesSetReady()
{
	verticiesReady = true;
}
template<typename T>
void  Mesh<T>::AddToVerticies(T vert)
{
	VerticiesMutex.lock();
	mingledWith = true;
	vertices.push_back(vert);
	VerticiesMutex.unlock();
}
template<typename T>
void  Mesh<T>::ClearVerticies()
{
	VerticiesMutex.lock();
	mingledWith = true;
	vertices.clear();
	VerticiesMutex.unlock();
}
*/