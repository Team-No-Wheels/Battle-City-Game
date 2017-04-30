#pragma once

#include "RendererService.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		class Renderer_DirectX final : public RendererService
		{
		public:
			/**
			Default constructor
			*/
			Renderer_DirectX();

			/**
			Default destructor
			*/
			~Renderer_DirectX();

			/**
			@brief Calls the appropriate render function.
			*/
			virtual void Render(uint32_t pTextureID, const Geometry::Rectangle& pSpriteBounds, const Geometry::Rectangle& pUVBounds) override;
		};
	}
}
