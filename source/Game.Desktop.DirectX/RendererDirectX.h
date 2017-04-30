#pragma once

#include "RendererService.h"

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
			*/
			virtual void Render(uint32_t pTextureID, const Geometry::Rectangle& pSpriteBounds, const Geometry::Rectangle& pUVBounds) override;
		};
	}
}
