#pragma once
#include "Sprite.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** Rendering class for WhiteBrick on the map.
		*/
		class WhiteBrick :public AnonymousEngine::Graphics::Sprite
		{
			ATTRIBUTED_DECLARATIONS(WhiteBrick, AnonymousEngine::Graphics::Sprite)

		public:
			WhiteBrick();
		};

		ENTITY_FACTORY_DECLARATIONS(WhiteBrick)
	}
}