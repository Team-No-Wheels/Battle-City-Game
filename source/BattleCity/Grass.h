#pragma once
#include "GameObject.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** GameObject class for Grass on the map.
		*/
		class Grass :public AnonymousEngine::Containers::GameObject
		{
			ATTRIBUTED_DECLARATIONS(Grass, AnonymousEngine::Containers::GameObject)

		public:
			/** Defaulted constructor.
			*/
			Grass() = default;

			/** Defaulted destructor.
			*/
			~Grass() = default;
		};

		ENTITY_FACTORY_DECLARATIONS(Grass)
	}
}