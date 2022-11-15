#pragma once
#include "Mesh.h"

class ChunkMesh : public Mesh
{public:
	ChunkMesh();

	void LinkVBOAttributes();
};