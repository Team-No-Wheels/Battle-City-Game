#pragma once

#include "RendererService.h"
#include "TextureLoaderService.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		class RendererDirectX final : public RendererService
		{
		public:
			/**
			Default constructor
			*/
			RendererDirectX();

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
			virtual void Render(Texture* pTexture, const Geometry::Rectangle& pSpriteBounds, const Geometry::Rectangle& pUVBounds) override;

			/**
				@brief Draw a rectangle with specified color.
			*/
			virtual void DrawRectangle(const Geometry::Rectangle& pRectangle, unsigned char pRed, unsigned char pGreen, unsigned char pBlue) override;
		};
	}
}
