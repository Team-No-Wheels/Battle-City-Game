#include "Pch.h"
#include "RendererDirectX.h"
#include "GameObject.h"
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

		void RendererDirectX::Render(const Sprite& pSprite) const
		{
			TextureDirectX* texture = static_cast<TextureDirectX*>(pSprite.GetTexture());
			texture;

			const Geometry::Rectangle& uvBounds = pSprite.GetUVBounds();
			const Geometry::Rectangle& spriteBounds = pSprite.GetRenderingBounds();
			uvBounds;
			spriteBounds;

			//mD3DDevice->SetTexture(0, texture->mTextureID);

			CUSTOMVERTEX* vertices = (CUSTOMVERTEX*)pVoid;

			v_buffer->Lock(0, 0, (void **)&vertices, NULL);//Lock the vertex buffer

			vertices[0].colour = D3DCOLOR_ARGB(255, 0, 0, 255);
			vertices[0].x = spriteBounds.BottomLeft.x;
			vertices[0].y = spriteBounds.BottomLeft.y;
			vertices[0].z = 0.0f;
			vertices[0].rhw = 1.0f;
			vertices[0].u = 0.0f;//1 - 0
			vertices[0].v = 0.0f;//1 - 0

			vertices[1].colour = D3DCOLOR_ARGB(0, 255, 0, 255);
			vertices[1].x = spriteBounds.BottomRight.x;
			vertices[1].y = spriteBounds.BottomRight.y;
			vertices[1].z = 0.0f;
			vertices[1].rhw = 1.0f;
			vertices[1].u = 1.0f;//0 - 1
			vertices[1].v = 0.0f;//0 - 0

			vertices[2].colour = D3DCOLOR_ARGB(0, 0, 255, 255);
			vertices[2].x = spriteBounds.TopRight.x;
			vertices[2].y = spriteBounds.TopRight.y;
			vertices[2].z = 0.0f;
			vertices[2].rhw = 1.0f;
			vertices[2].u = 1.0f;//0 - 1
			vertices[2].v = 1.0f;//0 - 0

			vertices[3].colour = D3DCOLOR_ARGB(0, 255, 0, 255);
			vertices[3].x = spriteBounds.TopLeft.x;
			vertices[3].y = spriteBounds.TopLeft.y;
			vertices[3].z = 0.0f;
			vertices[3].rhw = 1.0f;
			vertices[3].u = 0.0f;//0 - 1
			vertices[3].v = 1.0f;//0 - 0

			v_buffer->Unlock();//Unlock the vertex buffer

			// TODO : implement the draw function for renderer

			//mD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
			mD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(CUSTOMVERTEX));

		}

		void RendererDirectX::DrawRectangle(const Geometry::Rectangle& pRectangle, unsigned char pRed, unsigned char pGreen, unsigned char pBlue) const
		{
			pRectangle;
			pRed;
			pGreen;
			pBlue;
			// TODO : Draw rectangle

		}
	}
}