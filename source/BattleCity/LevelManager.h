#pragma once
#include "Vector.h"
#include "XmlParseMaster.h"
#include "WorldParserHelper.h"
#include "WorldSharedData.h"
#include "Service.h"
#include "TileBase.h"
#include "ActionFreeze.h"
#include "ActionMove.h"
#include "ActionShoot.h"

namespace BattleCity
{
	typedef MapEntities::TileType TileType;

	namespace Managers
	{
		
		/** LevelManager class which loads the entire levels of the game, transitions to a new level, returns the tile types for the map.
		*/
		class LevelManager : public AnonymousEngine::Core::Service
		{			
		public:
			/** Zero parameterized constructor.
			*	Initializes the private members of the class.
			*/
			LevelManager();

			/** Loads the 2-D array of Maptiles.
			*/
			void LoadLevelTiles(std::uint32_t levelNumber);

			/** Returns 2-D Vector array of MapTile enum type for the current level.
			*	@returns Returns 2-D Vector array of MapTile enum type for the current level.
			*/
			AnonymousEngine::Vector<AnonymousEngine::Vector<TileType>>& GetLevelTiles();

			/** Returns 2-D Vector array of MapTile enum type for the current level.
			*	@returns Returns 2-D Vector array of MapTile enum type for the current level.
			*/
			const AnonymousEngine::Vector<AnonymousEngine::Vector<TileType>>& GetLevelTiles() const;

			/** Loads the entire World XML, i.e. loads the XML for all levels.
			*	@returns Returns the loaded World.
			*/
			AnonymousEngine::Containers::World& LoadWorld();

			/** Deletes the dynamically allocated objects.
			*/
			~LevelManager();

			/** The name of the Service for level manager.
			*/
			static const std::string sServiceName;
		private:
			/** 2-D Vector array storing MapTile enum type
			*/
			AnonymousEngine::Vector<AnonymousEngine::Vector<TileType>> m2DTileArray;

			/** The name of the XML level file.
			*/
			static const std::string sLevelXmlFile;

			/** The attribute name of posX
			*/
			static const std::string sPosX;

			/** The attribute name of posY
			*/
			static const std::string sPosY;

			//Declaring the factories
			AnonymousEngine::ActionShootFactory actionShootFactory;
			AnonymousEngine::ActionFreezeFactory actionFreezeFactory;
			AnonymousEngine::ActionMoveFactory actionMoveFactory;

			/** Pointer to the parsed World object.
			*/
			AnonymousEngine::Containers::World* mWorld;
		};
	}
}