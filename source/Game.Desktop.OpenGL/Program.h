#pragma once

#include "GLFW/glfw3.h"
#include "SList.h"
#include "BattleCity.h"
#include "InputHandler.h"


namespace AnonymousEngine
{
	/** Program flow control and initialization handler
	* Handles the initialization of program window, OpenGL context and game loop
	*/
	class Program
	{
	public:
		/** Constructs a program object with the given display attributes
		*  @param width The width of the output window
		*  @param height The height of the output window
		*  @param title The title of the output window
		*/
		explicit Program(int width, int height, std::string title);
		/** Destroys the program instance freeing up and allocated resources
		*/
		~Program();
		/** Initializes the application
		*  This method creates the output window and initializes OpenGL context
		*/
		void Init();
		/** The game loop which runs through out the program
		*/
		void GameLoop();
		/** Shuts down the running program and terminates the output window.
		*/
		void ShutDown();
	private:
		// Output window width
		const int width;
		// Output window height
		const int height;
		// Output window title
		const std::string title;
		// Output window object
		GLFWwindow* window;
		// The object id of our shader program
		GLuint shaderProgram;
		// Vertex array object which contains the attributes of the stuff to draw
		GLuint VAO;

		// A single linked list object
		SList<int>* list;

		// Compiles all the shaders and links them to a program
		void InitShaders();
		// Draws the triangles on to screen
		void Draw();

		// BattleCity
		BattleCity::BattleCity* mBattleCity;

		static Program* thisProgram;
		// Keyboard input handler. Sets window close if ESC key is pressed.
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

		static const HashMap<int, InputType> KeyCodeToInputMap;
		static const HashMap<int, KeyState> KeyActionToKeyStateMap;
	};
}
