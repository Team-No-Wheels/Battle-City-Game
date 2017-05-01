#pragma once
#include "TileBase.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** GameObject class for BrownBrick in the map.
		*/
		class Brick :public TileBase
		{
			ATTRIBUTED_DECLARATIONS(Brick, TileBase)

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
