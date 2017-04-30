#include "Pch.h"
#include "MainMenuScreen.h"

namespace BattleCity
{
	MainMenuScreen::MainMenuScreen() : mCurrentOption(1)
	{
	}

	void MainMenuScreen::Update()
	{
	}

	CONCRETE_FACTORY_DEFINITIONS(UIScreen, MainMenuScreen);
}
