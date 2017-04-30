#pragma once
#include "Sprite.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** Rendering class for BrownBrick on the map.
		*/
		class Brick :public AnonymousEngine::Graphics::Sprite
		{
			ATTRIBUTED_DECLARATIONS(Brick, AnonymousEngine::Graphics::Sprite)

		public:
			Brick();
		};

		ENTITY_FACTORY_DECLARATIONS(Brick)
	}
}
