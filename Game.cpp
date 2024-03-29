#include "Game.h"
void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Window::GetInstance()->WinHeight = height;
	Window::GetInstance()->WinWidth = width;
	glViewport(0, 0, width, height);
}
void Game::RenderChunksInFrustum()
{
	

}
void Game::tickEntities()
{
	player.Update(timeDiff);
	for (auto it : world.entityMenager.EntityMap)
	{
		it.second->Tick(timeDiff);
	}


}
void Game::WorldUpdate()
{
	crntTime = glfwGetTime();
	timeDiff = crntTime - prevTime;
	prevTime = crntTime;
	counter++;
//	if (timeDiff >= 1.0 / 30.0)
	{
		
		
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = "Prodzekto - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(Window::GetInstance()->window, newTitle.c_str());
		

		counter = 0;
	}
	world.IdkWhatToCallThatForNow(player, timeDiff);
}
/*
void Game::GenChunksFromQueue(int amount)
{
	
	for (int i = 0; i < amount; i++)
	{
		if (ChunkGenQueue.empty()) return;
		glm::vec2 GenChunkOnPos = ChunkGenQueue.front();
		ChunkGenQueue.pop();
		auto it = World.find(GenChunkOnPos);
		if (it != World.end())
		{
			it->second.Generate(1);
			it->second.UpdateMesh();

		}
		
	}
}
void Game::PlaygroundForExperiments()
{
	glm::vec2 CurrentPos = Util::WorldPosToChunkPos(player.Position);
	for (int i = -RenderDistance*2; i <= RenderDistance*2; i++)
	{

		for (int k = -RenderDistance * 2; k <= RenderDistance * 2; k++)
		{
			glm::vec2 ChunkPos= glm::vec2(i,k)+ CurrentPos;
			World.emplace(std::make_pair<>(ChunkPos, Chunk(ChunkPos)));
			ChunkGenQueue.push(ChunkPos);
		}
	}

}
void Game::HandleWorldLoadingPositionChangeBased()
{

	 if (FramesTillResetQueue <= 0)
	 {
		// Chunk::BlockQueuesMap.clear();
		 FramesTillResetQueue = 1000;
		 std::cout << "Clearing the Q cycle (currently disabled)" << std::endl;
	 }
	 FramesTillResetQueue--;


	if (player.LastFrameChunkPos != Util::GetInstance()->WorldPosToChunkPos(player.Position))
	{
		glm::vec2 Dir =   Util::GetInstance()->WorldPosToChunkPos(player.Position) - player.LastFrameChunkPos;
		glm::vec2 toGenerate = glm::vec2(Dir.x * RenderDistance, Dir.y * RenderDistance);
		glm::vec2 toDelete = - glm::vec2(Dir.x * RenderDistance*2, Dir.y * RenderDistance*2) - Dir;
		glm::vec2 CurrentCenter = Util::GetInstance()->WorldPosToChunkPos(player.Position);
		for (int i = -RenderDistance; i <= RenderDistance; i++)
		{
			glm::vec2 NewChunkPos = (toGenerate + CurrentCenter) + glm::vec2(Dir.y * i, Dir.x * i);//swap is important here AND CORRECT

			auto it = World.find(NewChunkPos);
			if (it == World.end()) // if NOT in the world already
			{
				//Chunk* newChunk = new Chunk(NewChunkPos) ;
				//World.emplace(std::make_pair<>(NewChunkPos,newChunk)); 
				World.emplace(std::make_pair<>(NewChunkPos, Chunk(NewChunkPos)));

				ChunkGenQueue.push(NewChunkPos);
			}

		}
		for (int i = -RenderDistance*2; i <= RenderDistance*2; i++)
		{
			glm::vec2 DeleteChunkPos = (toDelete + CurrentCenter) + glm::vec2(Dir.y * i, Dir.x * i);//swap is important here AND CORRECT
			auto it = World.find(DeleteChunkPos);
			if (it != World.end())
			{
				World.erase(DeleteChunkPos);

			}
		}


		player.LastFrameChunkPos = CurrentCenter;
		
	}

}
void Game::HandleWorldLoadingDistanceBased() // ADD GENERATION OF NEW CHUNKS
{
	std::queue< glm::vec2> ToDelete;
	for (std::unordered_map<glm::vec2, Chunk>::iterator it = World.begin(); it != World.end(); it++)
	{
		if (glm::distance(it->first, Util::WorldPosToChunkPos(player.Position)) > RenderDistance*2)
		{
			
			ToDelete.push(it->first);
		}
	}
	for (int i = 0; i < ToDelete.size(); i++)
	{
		World.erase(ToDelete.front());
		ToDelete.pop();
	}
}*/
Game::Game()
{

	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window::GetInstance()->window = glfwCreateWindow(Window::GetInstance()->WinWidth,
		Window::GetInstance()->WinHeight, "This Is a Project. In English", NULL, NULL);
	// Error check if the window fails to create

	if (Window::GetInstance()->window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(Window::GetInstance()->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //GLAD init check, just in case
		std::cout << "Could not initialize GLAD!" << std::endl;
		glfwTerminate();

	}

	glfwSetInputMode(Window::GetInstance()->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glfwSetFramebufferSizeCallback(Window::GetInstance()->window, framebuffer_size_callback);
	glViewport(0, 0, Window::GetInstance()->WinWidth, -(Window::GetInstance()->WinHeight));
	//glfwSwapInterval(0);

	ShaderAndTextureStuff();
	world.SetShader(shaderProgram);
	Util::GetInstance()->LoadBlocks();
	player.world = &world;
	world.chunkMenager.SpawnChunks(player.Position);

	//PlaygroundForExperiments();
}

void Game::ShaderAndTextureStuff()
{
	shaderProgram = new Shader("ChunkShader.vert", "ChunkShader.frag");
	TranslucentShader = new Shader("ChunkShader.vert", "TransparentBlock.frag");
	EntityShader = new Shader("default.vert", "default.frag");


	 TextureAtlas = new Texture("textures/textureatlas.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	 /// For some reason its being saved to texture slot 2, not 0


	 ProtoAnimalTexture= new Texture("textures/ProtoAnimal.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGBA, GL_UNSIGNED_BYTE);

	world.renderer.ChunkShader = shaderProgram;
	world.renderer.TransparentBlockShader = TranslucentShader;
	world.renderer.EntityShader = EntityShader;


	TextureAtlas->texUnit(*shaderProgram, "tex0", 2);
	TextureAtlas->texUnit(*TranslucentShader, "tex0", 2); //values different than 2 just refuse to work, 0 idea why
	ProtoAnimalTexture->texUnit(*EntityShader, "tex0", 0);



	world.renderer.TextureAtlas = TextureAtlas;
	world.renderer.ProtoAnimalTexture= ProtoAnimalTexture;

	//TextureAtlas->Bind();

	player.SetShader(shaderProgram, EntityShader);
	player.Cam.GetUniformLocations(*shaderProgram);
	player.Cam.GetUniformLocationsForTransparent(*TranslucentShader);
	player.Cam.GetUniformLocationsForEntity(*EntityShader);


	player.Cam.UpdateView();
	player.Cam.UpdateUniformsTransparent();
	player.Cam.UpdateUniformsEntity();

}
