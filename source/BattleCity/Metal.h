#pragma once
#include "GameObject.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** GameObject class for Metal on the map.
		*/
		class Metal :public AnonymousEngine::Containers::GameObject
		{
			ATTRIBUTED_DECLARATIONS(Metal, AnonymousEngine::Containers::GameObject)

		public:
			/** Defaulted constructor.
			*/
			Metal() = default;
		
			/** Defaulted destructor.
			*/
			~Metal() = default;
		};

		ENTITY_FACTORY_DECLARATIONS(Metal)
	}
}