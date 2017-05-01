#pragma once
#include "TileBase.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** GameObject class for Grass on the map.
		*/
		class Grass :public TileBase
		{
			ATTRIBUTED_DECLARATIONS(Grass, TileBase)

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