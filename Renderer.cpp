#include "Renderer.h"
#include "Camera.h"
void Renderer::AddToChunkSet(std::shared_ptr<Chunk> ch)
{
	ChunkSet.emplace(ch);
}

void Renderer::AddToEntitiesSet(std::shared_ptr<Entity> e)
{
	EntitySet.emplace(e);
}

void Renderer::DrawChunks(Camera* cam)
{
	ChunkShader->Activate();

	cam->UpdateView();
	TextureAtlas->Bind();
	glDisable(GL_BLEND);
	for (auto it : ChunkSet)
	{
		it->DrawSolid(*ChunkShader);
	}
	
	TransparentBlockShader->Activate();
	cam->UpdateUniformsTransparent();
	//TextureAtlas->Bind();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto it : ChunkSet)
	{
		it->DrawTranslucent(*TransparentBlockShader);
	}
	ChunkSet.clear();
	DrawEntities(cam);

}

void Renderer::DrawEntities(Camera* cam)
{
	cam->UpdateUniformsEntity();
	EntityShader->Activate();
	ProtoAnimalTexture->Bind();
	for (auto it : EntitySet)
	{
		it->Draw(*EntityShader);
	}
}
