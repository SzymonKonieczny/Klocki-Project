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
	player.Update();
	


}
void Game::WorldUpdate()
{
	crntTime = glfwGetTime();
	timeDiff = crntTime - prevTime;
	counter++;
	if (timeDiff >= 1.0 / 30.0)
	{
		
		
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = "Prodzekto - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(Window::GetInstance()->window, newTitle.c_str());
		
		prevTime = crntTime;
		counter = 0;
	}
	world.IdkWhatToCallThatForNow(player);
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
	glfwSwapInterval(1);

	ShaderAndTextureStuff();
	world.SetShader(shaderProgram);
	Util::GetInstance()->LoadBlocks();
	player.world = &world;
	world.chunkMenager.SpawnChunks();

	//PlaygroundForExperiments();
}

void Game::ShaderAndTextureStuff()
{
	shaderProgram = new Shader("default.vert", "default.frag");
	 TextureAtlas = new Texture("textures/textureatlas.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	 PlayerTxt = new Texture("textures/Player.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

	TextureAtlas->texUnit(*shaderProgram, "tex0", 0);
	PlayerTxt->texUnit(*shaderProgram, "tex0", 1);
	
	TextureAtlas->Bind();

	player.SetShader(shaderProgram);
	player.Cam.GetUniformLocations(*shaderProgram);
	player.Cam.UpdateView(*shaderProgram);
}
