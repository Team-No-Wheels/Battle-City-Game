#pragma once
#include "Sprite.h"

namespace BattleCity
{
	namespace MapEntities
	{
		class WhiteBrick :public AnonymousEngine::Graphics::Sprite
		{
			ATTRIBUTED_DECLARATIONS(WhiteBrick, AnonymousEngine::Graphics::Sprite)

		public:
			WhiteBrick();
		};
	}
}