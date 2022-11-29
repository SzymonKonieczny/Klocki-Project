#pragma once
#include "Chunk.h"
#include <set>
#include "Enitity.h"
class Camera;

class Renderer
{
	std::set<std::shared_ptr<Chunk>> ChunkSet; //(Optimization) potentially I could also store ChunkPos, and avoid copying shared pointers
	std::set<std::shared_ptr<Entity>> EntitySet;
public :
	Shader* ChunkShader;
	Shader* EntityShader;
	Shader* TransparentBlockShader;

	Texture* TextureAtlas;
	Texture* ProtoAnimalTexture;


	void AddToChunkSet(std::shared_ptr<Chunk> ch);
	void AddToEntitiesSet(std::shared_ptr<Entity> e);

	void DrawChunks(Camera* cam);
	void DrawEntities(Camera* cam);


};
