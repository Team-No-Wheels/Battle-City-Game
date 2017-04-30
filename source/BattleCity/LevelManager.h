#pragma once
#include "Vector.h"

namespace BattleCity
{
	namespace Managers
	{
		/** Enum class for the type of tiles in the map.
		*/
		enum class MapTile
		{
			EMPTY,
			BRICK,
			METAL,
			GRASS,
			WATER,
			EAGLE
		};

		/** LevelManager class which loads the entire levels of the game, transitions to a new level, returns the tile types for the map.
		*/
		class LevelManager
		{
		public:
			/** Defaulted constructor.
			*/
			LevelManager() = default;

			AnonymousEngine::Vector<AnonymousEngine::Vector<MapTile>> GetLevelTiles();

			/** Defaulted destructor.
			*/
			~LevelManager() = default;
		};
	}
}