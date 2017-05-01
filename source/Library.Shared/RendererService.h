#pragma once
#include "HashMap.h"
#include "Service.h"
#include "Sprite.h"
#include "TextureLoaderService.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		/**
		The interface that should be implemented by texture loader for ServiceLocator pattern.
		*/
		class RendererService abstract : public Core::Service
		{
		public:
			/**
				@brief Calls the appropriate render function.
				@details Draw the texture with the UV and bounds as passed in params.
				@param[in] pTexture Texture to be drawn on screen
				@param[in] pSpriteBounds Bounds of the sprite
				@param[in] pUVBounds UV mapping
			*/
			virtual void Render(const Sprite& pSprite) const = 0;

			/**
				@brief Draw a rectangle with specified color.
			*/
			virtual void DrawRectangle(const Geometry::Rectangle& pRectangle, unsigned char pRed, unsigned char pGreen, unsigned char pBlue) const = 0;
		};
	}
}