#include "Pch.h"
#include "Program.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define WINDOW_TITLE	"Anonymous Engine Demo - OpenGL"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	// All program flow control is delegated to Program class
	AnonymousEngine::Program* program = new AnonymousEngine::Program(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	program->Init();
	program->GameLoop();
	program->ShutDown();
	return 0;
}
