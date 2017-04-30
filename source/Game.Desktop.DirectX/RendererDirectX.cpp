#include "Pch.h"
#include "RendererDirectX.h"

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

namespace AnonymousEngine
{
	namespace Graphics
	{
		RendererDirectX::RendererDirectX(IDirect3D9& pD3DInterface, IDirect3DDevice9& pD3DDevice) :
			mD3DInterface(&pD3DInterface), mD3DDevice(&pD3DDevice)
		{
			CUSTOMVERTEX vertices[] =
			{
				{ 320.0f, 50.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
				{ 520.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
				{ 120.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
			};

			v_buffer = nullptr;

			mD3DDevice->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
				0,
				CUSTOMFVF,
				D3DPOOL_MANAGED,
				&v_buffer,
				NULL);

			VOID* pVoid;    // a void pointer

							// lock v_buffer and load the vertices into it
			v_buffer->Lock(0, 0, (void**)&pVoid, 0);
			memcpy(pVoid, vertices, sizeof(vertices));
			v_buffer->Unlock();
		}

		RendererDirectX::~RendererDirectX()
		{
			v_buffer->Release();
		}

		void RendererDirectX::Render(Texture* pTexture, const Geometry::Rectangle& pSpriteBounds, const Geometry::Rectangle& pUVBounds)
		{
			pTexture;
			pSpriteBounds;
			pUVBounds;
			// TODO : implement the draw function for renderer

			// select which vertex format we are using
			mD3DDevice->SetFVF(CUSTOMFVF);

			// select the vertex buffer to display
			mD3DDevice->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

			// copy the vertex buffer to the back buffer
			mD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
		}

		void RendererDirectX::DrawRectangle(const Geometry::Rectangle& pRectangle, unsigned char pRed, unsigned char pGreen, unsigned char pBlue)
		{
			pRectangle;
			pRed;
			pGreen;
			pBlue;
			// TODO : Draw rectangle

		}
	}
}