#pragma once
#include "Mesh.h"

class ChunkMesh : public Mesh<CompressedVertex>
{public:
	ChunkMesh();

	void LinkVBOAttributes();
};