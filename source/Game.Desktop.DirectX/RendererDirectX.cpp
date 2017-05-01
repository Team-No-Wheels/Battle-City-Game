#include "Pch.h"
#include "RendererDirectX.h"
#include "TextureLoaderDirectX.h"

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_NORMAL | D3DFVF_TEX3)
namespace AnonymousEngine
{
	namespace Graphics
	{
		RendererDirectX::RendererDirectX(IDirect3D9& pD3DInterface, IDirect3DDevice9& pD3DDevice) :
			mD3DInterface(&pD3DInterface), mD3DDevice(&pD3DDevice)
		{
			CUSTOMVERTEX vertices[] =
			{
				{ 320.0f, 50.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), 0.0f, 1.0f },
				{ 520.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), 1.0f, 1.0f },
				{ 120.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), 1.0f, 0.0f},
				{ 120.0f, 50.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), 0.0f, 0.0f },
			};

			v_buffer = nullptr;

			mD3DDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
				0,
				CUSTOMFVF,
				D3DPOOL_MANAGED,
				&v_buffer,
				NULL);

			

							// lock v_buffer and load the vertices into it
			v_buffer->Lock(0, 0, (void**)&pVoid, 0);
			memcpy(pVoid, vertices, sizeof(vertices));
			v_buffer->Unlock();

			/*mD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			//mD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//mD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			mD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);*/


			// select which vertex format we are using
			mD3DDevice->SetFVF(CUSTOMFVF);

			// select the vertex buffer to display
			mD3DDevice->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
		}

		RendererDirectX::~RendererDirectX()
		{
			v_buffer->Release();
		}

		void RendererDirectX::Render(Texture* pTexture, const Geometry::Rectangle& pSpriteBounds, const Geometry::Rectangle& pUVBounds)
		{
			TextureDirectX* texture = static_cast<TextureDirectX*>(pTexture);
			texture;

			mD3DDevice->SetTexture(0, texture->mTextureID);

			mD3DDevice->BeginScene();

			CUSTOMVERTEX* vertices = (CUSTOMVERTEX*)pVoid;

			float x = 100.0f, y = 100.0f;

			v_buffer->Lock(0, 0, (void **)&vertices, NULL);//Lock the vertex buffer

			vertices[0].colour = D3DCOLOR_ARGB(255, 255, 255, 255);
			vertices[0].x = x;
			vertices[0].y = y;
			vertices[0].z = 0.0f;
			vertices[0].rhw = 1.0f;
			vertices[0].u = 0.0f;//1 - 0
			vertices[0].v = 0.0f;//1 - 0

			vertices[1].colour = D3DCOLOR_ARGB(255, 255, 255, 255);
			vertices[1].x = x + 64;
			vertices[1].y = y;
			vertices[1].z = 0.0f;
			vertices[1].rhw = 1.0f;
			vertices[1].u = 1.0f;//0 - 1
			vertices[1].v = 0.0f;//0 - 0

			vertices[2].colour = D3DCOLOR_ARGB(255, 255, 255, 255);
			vertices[2].x = x + 64;
			vertices[2].y = y + 64;
			vertices[2].z = 0.0f;
			vertices[2].rhw = 1.0f;
			vertices[2].u = 1.0f;//0 - 1
			vertices[2].v = 1.0f;//0 - 0

			vertices[3].colour = D3DCOLOR_ARGB(255, 255, 255, 255);
			vertices[3].x = x;
			vertices[3].y = y + 64;
			vertices[3].z = 0.0f;
			vertices[3].rhw = 1.0f;
			vertices[3].u = 0.0f;//0 - 1
			vertices[3].v = 1.0f;//0 - 0

			/*vertices[0].COLOR = D3DCOLOR_ARGB(255, 255, 255, 255);
			vertices[0].X = x;
			vertices[0].Y = y;
			vertices[0].Z = 0;
			vertices[0].RHW = 1;
			vertices[0].U = 0.0f;
			vertices[0].V = 0.0f;

			vertices[1].COLOR = D3DCOLOR_ARGB(255, 255, 255, 255);
			vertices[1].X = x + 100;
			vertices[1].Y = y;
			vertices[1].Z = 0;
			vertices[1].RHW = 1;
			vertices[1].U = 1.0f;
			vertices[1].V = 0.0f;

			vertices[2].COLOR = D3DCOLOR_ARGB(255, 255, 255, 255);
			vertices[2].X = x + 100;
			vertices[2].Y = y + 100;
			vertices[2].Z = 0;
			vertices[2].RHW = 1;
			vertices[2].U = 1.0f;
			vertices[2].V = 1.0f;

			vertices[3].COLOR = D3DCOLOR_ARGB(255, 255, 255, 255);
			vertices[3].X = x;
			vertices[3].Y = y + 100;
			vertices[3].Z = 0;
			vertices[3].RHW = 1;
			vertices[3].U = 0.0f;
			vertices[3].V = 1.0f;*/


			v_buffer->Unlock();//Unlock the vertex buffer

			pTexture;
			pSpriteBounds;
			pUVBounds;
			// TODO : implement the draw function for renderer

			
			

			

			// copy the vertex buffer to the back buffer
			//mD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
			mD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(CUSTOMVERTEX));

			mD3DDevice->EndScene();
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