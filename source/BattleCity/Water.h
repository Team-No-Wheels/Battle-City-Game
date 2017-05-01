#pragma once
#include "TileBase.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** GameObject class for Water on the map.
		*/
		class Water :public TileBase
		{
			ATTRIBUTED_DECLARATIONS(Water, TileBase)

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
