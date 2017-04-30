#pragma once
#include "Vector.h"
#include "XmlParseMaster.h"
#include "WorldParserHelper.h"
#include "WorldSharedData.h"

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
			/** Zero parameterized constructor.
			*	Initializes the private members of the class.
			*/
			LevelManager();

			/** Returns 2-D Vector array of MapTile enum type for the current level.
			*	@returns Returns 2-D Vector array of MapTile enum type for the current level.
			*/
			AnonymousEngine::Vector<AnonymousEngine::Vector<MapTile>>& GetLevelTiles();

			/** Returns 2-D Vector array of MapTile enum type for the current level.
			*	@returns Returns 2-D Vector array of MapTile enum type for the current level.
			*/
			const AnonymousEngine::Vector<AnonymousEngine::Vector<MapTile>>& GetLevelTiles() const;

			/** Loads the entire World XML, i.e. loads the XML for all levels.
			*	@returns Returns the loaded World.
			*/
			AnonymousEngine::Containers::World& LoadWorld();

			/** Deletes the dynamically allocated objects.
			*/
			~LevelManager();

		private:
			/** 2-D Vector array storing MapTile enum type
			*/
			AnonymousEngine::Vector<AnonymousEngine::Vector<MapTile>> m2DTileArray;

			/** The name of the XML level file.
			*/
			static const std::string mLevelXmlFile;

			/** Pointer to the parsed World object.
			*/
			AnonymousEngine::Containers::World* mWorld;
		};
	}
}