#pragma once
#include "Sprite.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** Rendering class for WhiteBrick on the map.
		*/
		class Metal :public AnonymousEngine::Graphics::Sprite
		{
			ATTRIBUTED_DECLARATIONS(Metal, AnonymousEngine::Graphics::Sprite)

		public:
			Metal();
		};

		ENTITY_FACTORY_DECLARATIONS(Metal)
	}
}