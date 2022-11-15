#pragma once
#include "Mesh.h"
class CompassMesh : public Mesh<UncompressedVertex>
{

public:
	
	void LinkVBOAttributes() override
	{

		VAO.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(CompressedVertex), (void*)0);
		VAO.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(CompressedVertex), (void*)(3 * sizeof(float)));
		VAO.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(CompressedVertex), (void*)(6 * sizeof(float)));


	};

	CompassMesh()
	{
		LinkVBOAttributes();
	}



	

};