#include "Mesh.h"

/*Mesh::Mesh(std::vector<Vertex>& vertices_, std::vector < GLuint>& indices_)
{
	Mesh::vertices = vertices_;
	Mesh::indices = indices_;
	Mesh::model = glm::mat4(1.0);
	// Generates Vertex Array Object and binds it
	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO1 = new VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	//EBO1 = new EBO(indices);

	// Links VBO to VAO
	VAO.LinkAttrib(*VBO1, 0, 3, GL_FLOAT,  sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(*VBO1, 1, 3, GL_FLOAT,  sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(*VBO1, 2, 2, GL_FLOAT,  sizeof(Vertex), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO1->Unbind();
	//EBO1->Unbind();

}*/
Mesh::Mesh(): VBO1(vertices)
{

	// Generates Vertex Array Object and binds it

	VAO.Bind();



	// Links VBO to VAO
	VAO.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO1.Unbind();
	//EBO1->Unbind();

}
Mesh::~Mesh()
{

}
void Mesh::Draw(Shader& shader, glm::vec3 Position, bool UseModelMatrix)  {

	shader.Activate();
	if (mingledWith)
	{
		VBO1.Rebuffer(vertices);
		mingledWith = false;
	}

	//EBO1->Rebuffer(indices);
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

std::vector<Vertex>& Mesh::GetVertexVector()
{
	mingledWith = true;
	return vertices;
}

void Mesh::AddToVerticies(Vertex vert)
{
	mingledWith = true;
	vertices.push_back(vert);
}

void Mesh::ClearVerticies()
{
	mingledWith = true;
	vertices.clear();
}
