#include "ChunkMesh.h"

ChunkMesh::ChunkMesh()
{
	LinkVBOAttributes();
}

void ChunkMesh::LinkVBOAttributes()
{

	VAO.LinkAttrib(VBO1, 0, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*)0);

}