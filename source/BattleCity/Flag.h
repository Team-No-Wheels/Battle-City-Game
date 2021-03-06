#pragma once
#include "TileBase.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** GameObject class for Grass on the map.
		*/
		class Flag final: public TileBase
		{
			ATTRIBUTED_DECLARATIONS(Flag, TileBase)

		public:
			/** Defaulted constructor.
			*/
			Flag();

			/** Defaulted destructor.
			*/
			~Flag() = default;
		};

		ENTITY_FACTORY_DECLARATIONS(Flag)
	}
}