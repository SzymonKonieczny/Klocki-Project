#include "Game.h"
void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Window::GetInstance()->WinHeight = height;
	Window::GetInstance()->WinWidth = width;
	glViewport(0, 0, width, height);
}
void Game::RenderChunksInFrustum()
{
	if (chunk == nullptr) return;

	chunk->Draw(*shaderProgram);
}
void Game::tickEntities()
{
	player.Update();
}
void Game::PlaygroundForExperiments()
{

	chunk = new Chunk(glm::vec2(1, 0));
	chunk->Generate(2);
	chunk->UpdateMesh();
}
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


	PlaygroundForExperiments();
}

void Game::ShaderAndTextureStuff()
{
	shaderProgram = new Shader("default.vert", "default.frag");
	 TextureAtlas = new Texture("textures/grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	 PlayerTxt = new Texture("textures/Player.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

	TextureAtlas->texUnit(*shaderProgram, "tex0", 0);
	PlayerTxt->texUnit(*shaderProgram, "tex0", 1);
	
	TextureAtlas->Bind();

	player.SetShader(shaderProgram);
	player.Cam.GetUniformLocations(*shaderProgram);
	player.Cam.UpdateView(*shaderProgram);
}
