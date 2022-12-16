#pragma once
#include "Mesh.h"
class EntityMesh : public Mesh<UncompressedVertex>
{
	void LinkVBOAttributes() override
	{

		VAO.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(UncompressedVertex), (void*)0, false);
		VAO.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(UncompressedVertex), (void*)(3 * sizeof(float)), false);
		VAO.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(UncompressedVertex), (void*)(6 * sizeof(float)), false);

		VAO.Bind();
		EBO1.Bind();
		VAO.Unbind();

	};
public:
	EntityMesh()
	{
		UseElementsBuffer = true;

		LinkVBOAttributes();
	}
};