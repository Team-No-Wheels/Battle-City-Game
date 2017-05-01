#pragma once
#include "TileBase.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** GameObject class for Metal on the map.
		*/
		class Metal :public TileBase
		{
			ATTRIBUTED_DECLARATIONS(Metal, TileBase)

		public:
			/** Defaulted constructor.
			*/
			Metal();
		
			/** Defaulted destructor.
			*/
			~Metal() = default;
		};

		ENTITY_FACTORY_DECLARATIONS(Metal)
	}
}