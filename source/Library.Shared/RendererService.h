#pragma once
#include "HashMap.h"
#include "Service.h"
#include "Rectangle.h"

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
			*/
			virtual void Render(uint32_t pTextureID, const Geometry::Rectangle& pSpriteBounds, const Geometry::Rectangle& pUVBounds) = 0;

		};
	}
}