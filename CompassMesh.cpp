#include "CompassMesh.h"

CompassMesh::CompassMesh()
{
	LinkVBOAttributes();
}

void CompassMesh::LinkVBOAttributes()
{
	
		VAO.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		VAO.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		VAO.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	

}