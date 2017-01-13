#include "Pch.h"
#include "Program.h"
#include <fstream>

namespace Game
{
	Program::Program(int width, int height, std::string title)
		: width(width), height(height), title(title), window(nullptr)
	{
		// Using code from Library.Desktop
		list = new Library::SList();
	}

	Program::~Program()
	{
		delete list;
	}

	void Program::Init()
	{
		// Initalize window parameters
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// create window
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (window == nullptr)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window");
		}
		glfwMakeContextCurrent(window);

		// initalize viewport		
		glfwGetFramebufferSize(window, nullptr, nullptr);
		glViewport(0, 0, width, height);

		// register keyboard handler
		glfwSetKeyCallback(window, KeyCallback);
	}

	void Program::GameLoop()
	{
		// game loop exiting on window close or ESC keypress
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
			Draw();
			glfwSwapBuffers(window);
		}
	}

	void Program::ShutDown()
	{
		glfwTerminate();
	}

	void Program::Draw()
	{
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Program::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		UNREFERENCED_PARAMETER(scancode);
		// if ESC key is pressed and there are no modifier keys pressed, ask to close the output window
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && mode == 0)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}
