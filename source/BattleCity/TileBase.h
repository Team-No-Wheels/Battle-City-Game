#pragma once
#include "GameObject.h"

namespace BattleCity
{
	namespace MapEntities
	{
		/** Enum class for the Tile Type.
		*/
		enum class TileType
		{
			EMPTY,
			BRICK,
			METAL,
			GRASS,
			WATER,
			FLAG
		};

		/** Base GameObject class for all the tiles
		*/
		class TileBase : public AnonymousEngine::Core::GameObject
		{
			ATTRIBUTED_DECLARATIONS(TileBase, AnonymousEngine::Core::GameObject)

		public:
			/** Parameterized constructor.
			*	@param tileType The enum tile type of the class.
			*/
			TileBase(TileType tileType);

			/** Defaulted destructor.
			*/
			virtual ~TileBase() = default;
		protected:
			/** The tile type of the class.
			*/
			TileType mTileType;
		};
	}
}