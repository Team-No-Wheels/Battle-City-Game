#include "Pch.h"
#include "LevelManager.h"
#include "Brick.h"
#include "FrameManager.h"
#include "Grass.h"
#include "Metal.h"
#include "Water.h"
#include "World.h"
#include "Sector.h"
#include "ServiceLocator.h"
#include "UIElement.h"
#include "PowerUp.h"

using namespace AnonymousEngine;

namespace BattleCity
{
	namespace Managers
	{
		const std::string LevelManager::sPosX = "posX";
		const std::string LevelManager::sPosY = "posY";

		typedef Parsers::XmlParseMaster XmlParseMaster;
		typedef Parsers::WorldParserHelper WorldParserHelper;
		typedef Parsers::WorldSharedData WorldSharedData;
		typedef MapEntities::BrickFactory BrickFactory;
		typedef MapEntities::GrassFactory GrassFactory;
		typedef MapEntities::MetalFactory MetalFactory;
		typedef MapEntities::WaterFactory WaterFactory;
		typedef Graphics::FrameManagerFactory FrameManagerFactory;
		typedef Graphics::FrameFactory FrameFactory;
		typedef Containers::World World;
		typedef Containers::Sector Sector;

		const std::string LevelManager::sServiceName = "LevelManager";
		const std::string LevelManager::sLevelXmlFile = "resources\\BattleCity.xml";

		LevelManager::LevelManager()
			:mWorld(nullptr)
		{
			Core::ServiceLocator::AddService(sServiceName, *this);
		}

		void LevelManager::LoadLevelTiles(std::uint32_t levelNumber)
		{
			assert(mWorld != nullptr);
			Datum& sectorDatum = mWorld->Sectors();
			Sector& currentLevel = static_cast<Sector&>(sectorDatum.Get<Scope>(levelNumber));
			currentLevel;
		}

		Vector<Vector<TileType>>& LevelManager::GetLevelTiles()
		{
			return const_cast<Vector<Vector<TileType>>&>(const_cast<const LevelManager*>(this)->GetLevelTiles());
		}

		const Vector<Vector<TileType>>& LevelManager::GetLevelTiles() const
		{
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
			FrameManagerFactory frameManagerFactory;
			FrameFactory frameFactory;
			UIElementFactory uiElementFactory;
			PowerUpFactory powerUpFactory;
			TankPlayerFactory tankPlayerFactory;
			ActionShootFactory actionShootFactory;
			ActionMoveFactory actionMoveFactory;

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