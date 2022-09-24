#include "Renderer.h"

void Renderer::AddToSet(std::shared_ptr<Chunk> ch)
{
	ChunkSet.emplace(ch);
}

void Renderer::DrawChunks()
{
	glDisable(GL_BLEND);
	TextureAtlas->Bind();
	for (auto it : ChunkSet)
	{
		it->DrawSolid(*ChunkShader);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto it : ChunkSet)
	{
		it->DrawTranslucent(*TransparentBlockShader);
	}
	ChunkSet.clear();

}
