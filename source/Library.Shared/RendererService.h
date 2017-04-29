#pragma once
#include "HashMap.h"
#include "Service.h"

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
			virtual void Render() = 0;

		};
	}
}