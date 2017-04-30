#pragma once
#include "GameObject.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** GameObject class for BrownBrick in the map.
		*/
		class Brick :public AnonymousEngine::Containers::GameObject
		{
			ATTRIBUTED_DECLARATIONS(Brick, AnonymousEngine::Containers::GameObject)

		public:
			/** Defaulted constructor.
			*/
			Brick() = default;

			/** Defaulted destructor.
			*/
			~Brick() = default;
		};

		ENTITY_FACTORY_DECLARATIONS(Brick)
	}
}