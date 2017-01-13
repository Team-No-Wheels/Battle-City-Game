#pragma once

#include "GLFW/glfw3.h"
#include "SList.h"

namespace Game
{
	/** Program flow control and initalization handler
	 * Handles the initalization of program window, OpenGL context and game loop
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
		*  This method creats the output window and initalizes opengl context
		*/
		void Init();
		/** The game loop which runs throughtout the program
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
		
		// A single linked list object
		Library::SList* list;
				
		// Draws the triangles on to screen
		void Draw();
		// Keyboard input handler. Sets window close if ESC key is pressed.
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	};
}
