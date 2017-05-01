#include "Pch.h"
#include <d3d11.h>
#include "SList.h"
#include "EngineSettings.h"
#include "BattleCity.h"
#include "ServiceLocator.h"
#include "TextureLoaderDirectX.h"
#include "RendererDirectX.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define WINDOW_TITLE	L"Anonymous Engine Demo - DirectX"

#define DX_VERSION 9

#if DX_VERSION == 11
// global declarations
IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
ID3D11Device *dev;                     // the pointer to our Direct3D device interface
ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
ID3D11RenderTargetView *backbuffer;    // the pointer to our back buffer
#endif



#if DX_VERSION == 9
IDirect3D9* d3d;    // the pointer to our Direct3D interface
IDirect3DDevice9* d3ddev;    // the pointer to the device class
#endif
									   // function prototypes
void InitD3D(HWND hWnd);    // sets up and initializes Direct3D
void RenderFrame(void);     // renders a single frame
void CleanD3D(void);        // closes Direct3D and releases memory

							// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Using library code from DirectX project
	AnonymousEngine::SList<int>* list = new AnonymousEngine::SList<int>();
	list->PushFront(10);
	list->PopFront();

	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	RECT wr = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(NULL,
		L"WindowClass",
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	InitD3D(hWnd);
	AnonymousEngine::Core::EngineSettings::SetPlatform(AnonymousEngine::Core::PlatformType::DirectX);
	AnonymousEngine::Core::EngineSettings::SetScreenWidth(WINDOW_WIDTH);
	AnonymousEngine::Core::EngineSettings::SetScreenHeight(WINDOW_HEIGHT);

	// setting up the ServiceLocator
	// registering TextureLoader
	AnonymousEngine::Graphics::TextureLoaderDirectX textureLoader(*d3ddev);
	AnonymousEngine::Core::ServiceLocator::AddService(AnonymousEngine::Core::ServiceLocator::sTextureLoader, textureLoader);
	// registering Renderer
	AnonymousEngine::Graphics::RendererDirectX renderer(*d3d, *d3ddev);
	AnonymousEngine::Core::ServiceLocator::AddService(AnonymousEngine::Core::ServiceLocator::sRenderer, renderer);

	BattleCity::BattleCity* battleCity = new BattleCity::BattleCity();
	battleCity->Init();
	// enter the main loop:

	MSG msg;

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}


		//RenderFrame();
#if DX_VERSION == 11
		// clear the back buffer to a deep blue
		const float colorRGBA[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
		devcon->ClearRenderTargetView(backbuffer, colorRGBA);

		// do 3D rendering on the back buffer here
		battleCity->Update(1.0f / 60.0f);

		// switch the back buffer and the front buffer
		swapchain->Present(0, 0);
#endif

#if DX_VERSION == 9
		// clear the window to a deep blue
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

		// begins the 3D scene
		//d3ddev->BeginScene();

		// do 3D rendering on the back buffer here
		battleCity->Update(1.0f / 60.0f);

		// ends the 3D scene
		//d3ddev->EndScene();

		d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
#endif
	}

	// clean up DirectX and COM
	CleanD3D();
	return static_cast<int>(msg.wParam);
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void InitD3D(HWND hWnd)
{
#if DX_VERSION == 11
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = hWnd;                                // the window to be used
	scd.SampleDesc.Count = 1;                               // how many multisamples
	scd.SampleDesc.Quality = 0;                             // multisample quality level
	scd.Windowed = TRUE;                                    // windowed/full-screen mode

															// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);


	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer address to create the render target
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);


	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = WINDOW_WIDTH;
	viewport.Height = WINDOW_HEIGHT;

	devcon->RSSetViewports(1, &viewport);
#endif
#if DX_VERSION == 9
	d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D


								   // create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);
#endif
}


// this is the function used to render a single frame
void RenderFrame(void)
{
	

	

	
}


// this is the function that cleans up Direct3D and COM
void CleanD3D(void)
{
#if DX_VERSION == 11
	// close and release all existing COM objects
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
#endif
#if DX_VERSION == 9
	d3ddev->Release();    // close and release the 3D device
	d3d->Release();    // close and release Direct3D
#endif
}
