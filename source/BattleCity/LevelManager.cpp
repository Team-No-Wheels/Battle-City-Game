#include "Pch.h"
#include "LevelManager.h"
#include "Brick.h"
#include "Grass.h"
#include "Metal.h"
#include "Water.h"
#include "World.h"
#include "ServiceLocator.h"

using namespace AnonymousEngine;

namespace BattleCity
{
	namespace Managers
	{
		typedef Parsers::XmlParseMaster XmlParseMaster;
		typedef Parsers::WorldParserHelper WorldParserHelper;
		typedef Parsers::WorldSharedData WorldSharedData;		
		typedef MapEntities::BrickFactory BrickFactory;
		typedef MapEntities::GrassFactory GrassFactory;
		typedef MapEntities::MetalFactory MetalFactory;
		typedef MapEntities::WaterFactory WaterFactory;
		typedef Containers::World World;

		const std::string LevelManager::sServiceName = "LevelManager";
		const std::string LevelManager::sLevelXmlFile = "LevelFile.xml";

		LevelManager::LevelManager()
			:mWorld(nullptr)
		{
			Core::ServiceLocator::AddService(sServiceName, *this);
		}

		Vector<Vector<MapTile>>& LevelManager::GetLevelTiles(std::uint32_t levelNumber)
		{
			return const_cast<Vector<Vector<MapTile>>&>(const_cast<const LevelManager*>(this)->GetLevelTiles(levelNumber));
		}

		const Vector<Vector<MapTile>>& LevelManager::GetLevelTiles(std::uint32_t levelNumber) const

		{
			UNREFERENCED_PARAMETER(levelNumber);
			return m2DTileArray;
		}

		World& LevelManager::LoadWorld()
		{
			//Resetting
			delete mWorld;			

			//Declaring the factories
			BrickFactory brickFactory;
			GrassFactory grassFactory;
			WaterFactory waterFactory;
			MetalFactory metalFactory;

			//Start parsing xml file.
			WorldSharedData worldSharedData;
			XmlParseMaster xmlParseMaster(worldSharedData);
			WorldParserHelper worldParseHelper;

			xmlParseMaster.AddHelper(worldParseHelper);
			xmlParseMaster.ParseFromFile(sLevelXmlFile);

			mWorld = worldSharedData.ExtractWorld();

			return *mWorld;
		}

		LevelManager::~LevelManager()
		{
			delete mWorld;
		}
	}
}