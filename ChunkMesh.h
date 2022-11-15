#pragma once
#include "Mesh.h"

class ChunkMesh : public Mesh<Vertex>
{public:
	ChunkMesh();

	void LinkVBOAttributes();
};