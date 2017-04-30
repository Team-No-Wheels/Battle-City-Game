#pragma once
#include "Sprite.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** Rendering class for BrownBrick on the map.
		*/
		class BrownBrick :public AnonymousEngine::Graphics::Sprite
		{
			ATTRIBUTED_DECLARATIONS(BrownBrick, AnonymousEngine::Graphics::Sprite)

		public:
			BrownBrick();
		};

		ENTITY_FACTORY_DECLARATIONS(BrownBrick)
	}
}
