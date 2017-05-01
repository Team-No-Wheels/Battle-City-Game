#include "Pch.h"
#include "MainMenuScreen.h"

namespace BattleCity
{
	ATTRIBUTED_DEFINITIONS(MainMenuScreen);

	MainMenuScreen::MainMenuScreen() : mCurrentOption(StartGame)
	{
	}

	void MainMenuScreenUpdate(AnonymousEngine::Containers::WorldState&)
	{
	}

	CONCRETE_FACTORY_DEFINITIONS(UIScreen, MainMenuScreen);
}
