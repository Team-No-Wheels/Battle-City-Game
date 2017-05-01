#include "Pch.h"
#include "Program.h"
#include "EngineSettings.h"
#include "ServiceLocator.h"
#include "TextureLoaderOpenGL.h"
#include "RendererOpenGL.h"

#define WINDOW_WIDTH	256 * 4
#define WINDOW_HEIGHT	240 * 4
#define WINDOW_TITLE	"Anonymous Engine Demo - OpenGL"
#define OpenGL

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	// setting the engine parameters.
	AnonymousEngine::Core::EngineSettings::SetPlatform(AnonymousEngine::Core::PlatformType::DirectX);
	AnonymousEngine::Core::EngineSettings::SetScreenWidth(WINDOW_WIDTH);
	AnonymousEngine::Core::EngineSettings::SetScreenHeight(WINDOW_HEIGHT);

	// setting up the ServiceLocator
	// registering TextureLoader
	AnonymousEngine::Graphics::TextureLoaderOpenGL mTextureLoader;
	AnonymousEngine::Core::ServiceLocator::AddService(AnonymousEngine::Core::ServiceLocator::sTextureLoader, mTextureLoader);
	// registering Renderer
	AnonymousEngine::Graphics::RendererOpenGL mRenderer;
	AnonymousEngine::Core::ServiceLocator::AddService(AnonymousEngine::Core::ServiceLocator::sRenderer, mRenderer);

	// All program flow control is delegated to Program class
	AnonymousEngine::Program* program = new AnonymousEngine::Program(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	program->Init();
	program->GameLoop();
	program->ShutDown();
	return 0;
}
