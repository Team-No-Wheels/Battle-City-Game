#pragma once
#include "GameObject.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** GameObject class for Grass on the map.
		*/
		class Flag :public AnonymousEngine::Core::GameObject
		{
			ATTRIBUTED_DECLARATIONS(Flag, AnonymousEngine::Core::GameObject)

		public:
			/** Defaulted constructor.
			*/
			Flag() = default;

			/** Defaulted destructor.
			*/
			~Flag() = default;
		};

		ENTITY_FACTORY_DECLARATIONS(Flag)
	}
}