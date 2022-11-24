#pragma once
#include "Mesh.h"
class CompassMesh : public Mesh<UncompressedVertex>
{

public:
	
	void LinkVBOAttributes() override
	{

		VAO.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(UncompressedVertex), (void*)0, false);
		VAO.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(UncompressedVertex), (void*)(3 * sizeof(float)), false);
		VAO.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(UncompressedVertex), (void*)(6 * sizeof(float)), false);


	};

	CompassMesh()
	{
		LinkVBOAttributes();
	}



	

};