#pragma once
#include "Sprite.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** Rendering class for Grass on the map.
		*/
		class Grass :public AnonymousEngine::Graphics::Sprite
		{
			ATTRIBUTED_DECLARATIONS(Grass, AnonymousEngine::Graphics::Sprite)

		public:
			Grass();
		};

		ENTITY_FACTORY_DECLARATIONS(Grass)
	}
}