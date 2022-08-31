#pragma once
#ifndef WINDOW_H 
#define WINDOW_H 
#include<GLFW/glfw3.h>
class Window {

	Window();

	static Window* instance;

public:
	static Window* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Window();
		}
		return instance;
	}
	Window(Window& other) = delete;
	void operator=(const Window&) = delete;

	GLFWwindow* window = nullptr;
	 int WinHeight = 720;
	 int  WinWidth = 1280;




};

#endif // !WINDOW_H 
