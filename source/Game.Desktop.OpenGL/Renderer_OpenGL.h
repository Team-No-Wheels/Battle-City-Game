#pragma once
#include "RendererService.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		class Renderer_OpenGL final : public RendererService
		{
		public:
			/**
				Default constructor
			*/
			Renderer_OpenGL();

			/**
				Default destructor
			*/
			~Renderer_OpenGL();

			/**
				@brief Calls the appropriate render function.
			*/
			virtual void Render(uint32_t pTextureID, const Geometry::Rectangle& pSpriteBounds, const Geometry::Rectangle& pUVBounds) override;
		};
	}
}