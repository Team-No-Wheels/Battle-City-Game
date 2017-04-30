#include "Pch.h"
#include "LevelManager.h"
#include "Brick.h"
#include "Grass.h"
#include "Metal.h"

using namespace AnonymousEngine;

namespace BattleCity
{
	namespace Managers
	{
		typedef AnonymousEngine::Parsers::XmlParseMaster XmlParseMaster;
		typedef AnonymousEngine::Parsers::WorldParserHelper WorldParserHelper;
		typedef AnonymousEngine::Parsers::WorldSharedData WorldSharedData;

		const std::string mLevelXmlFile = "LevelFile.xml";

		LevelManager::LevelManager()
			:m2DTileArray()
		{
		}

		Vector<Vector<MapTile>>& LevelManager::GetLevelTiles()
		{
			return const_cast<Vector<Vector<MapTile>>&>(const_cast<const LevelManager*>(this)->GetLevelTiles());
		}

		const Vector<Vector<MapTile>>& LevelManager::GetLevelTiles() const
		{
			return m2DTileArray;
		}

		void LevelManager::LoadWorld()
		{
			WorldSharedData worldSharedData;
			XmlParseMaster xmlParseMaster(worldSharedData);
			WorldParserHelper worldParseHelper;

			xmlParseMaster.AddHelper(worldParseHelper);
			xmlParseMaster.ParseFromFile(mLevelXmlFile);
		}
	}
}