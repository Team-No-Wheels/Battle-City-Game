#include "Pch.h"
#include "RendererDirectX.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		RendererDirectX::RendererDirectX()
		{

		}

		RendererDirectX::~RendererDirectX()
		{

		}

		void RendererDirectX::Render(Texture* pTexture, const Geometry::Rectangle& pSpriteBounds, const Geometry::Rectangle& pUVBounds)
		{
			pTexture;
			pSpriteBounds;
			pUVBounds;
			// TODO : implement the draw function for renderer
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