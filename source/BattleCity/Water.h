#pragma once
#include "GameObject.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** GameObject class for Water on the map.
		*/
		class Water :public AnonymousEngine::Core::GameObject
		{
			ATTRIBUTED_DECLARATIONS(Water, AnonymousEngine::Core::GameObject)

		public:
			/** Defaulted constructor.
			*/
			Water() = default;

			/** Defaulted destructor.
			*/
			~Water() = default;
		};

		ENTITY_FACTORY_DECLARATIONS(Water)
	}
}
