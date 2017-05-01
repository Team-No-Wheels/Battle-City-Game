#pragma once

#include "RendererService.h"
#include "TextureLoaderService.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		//struct CustomVertex { FLOAT X, Y, Z, RHW; DWORD COLOR; };
		/*struct CUSTOMVERTEX
		{
			float X, Y, Z, RHW;    // from the D3DFVF_XYZRHW flag
			DWORD COLOR;    // from the D3DFVF_DIFFUSE flag
			float U, V;
		};*/

		struct CUSTOMVERTEX
		{
			float x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
			DWORD colour;    // from the D3DFVF_DIFFUSE flag
			float u, v;
		};

		//Custom vertex
		/*struct TLVERTEX
		{
			float x;
			float y;
			float z;
			float rhw;
			D3DCOLOR colour;
			float u;
			float v;
		};*/


		class RendererDirectX final : public RendererService
		{
		public:
			/**
				Default constructor
			*/
			RendererDirectX(IDirect3D9& pD3DInterface, IDirect3DDevice9& pD3DDevice);

			/**
				Default destructor
			*/
			~RendererDirectX();

			/**
				@brief Calls the appropriate render function.
				@details Draw the texture with the UV and bounds as passed in params.
				@param[in] pTexture Texture to be drawn on screen
				@param[in] pSpriteBounds Bounds of the sprite
				@param[in] pUVBounds UV mapping
			*/
			virtual void Render(const Sprite& pSprite) const override;

			/**
				@brief Draw a rectangle with specified color.
			*/
			virtual void DrawRectangle(const Geometry::Rectangle& pRectangle, unsigned char pRed, unsigned char pGreen, unsigned char pBlue) const override;
		private:
			/**
				The pointer to our Direct3D interface.
			*/
			IDirect3D9* mD3DInterface;

			/**
				The pointer to the device class.
			*/
			IDirect3DDevice9* mD3DDevice;

			IDirect3DVertexBuffer9* v_buffer;
			VOID* pVoid;    // a void pointer

			//TLVERTEX* vertices;
			
			//ID3DXSprite* mSprite;
		};
	}
}
