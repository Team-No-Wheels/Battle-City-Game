#include "Pch.h"
#include "UIManager.h"

namespace BattleCity
{
	AnonymousEngine::HashMap<UIManager::UiType, std::string> UIManager::ScreenClassNames =
	{
		{UiType::MainMenu, "MainMenu"},
		{UiType::LevelIntro, "LevelIntro"},
		{UiType::InGame, "InGame"},
		{UiType::Pause, "Pause"},
		{UiType::GameOver, "GameOver"},
		{UiType::LevelComplete, "LevelComplete"}
	};

	void UIManager::ActivateUiScreen(UiType uiType)
	{
		if (!mActiveUiScreens.ContainsKey(uiType))
		{
			mActiveUiScreens[uiType] = AnonymousEngine::Factory<UIScreen>::Create(ScreenClassNames[uiType]);
		}
	}

	void UIManager::DeactivateUiScreen(UiType uiType)
	{
		if (mActiveUiScreens.ContainsKey(uiType))
		{
			mActiveUiScreens.Remove(uiType);
		}
	}

	void UIManager::Update()
	{
		for (auto& entry : mActiveUiScreens)
		{
			entry.second->Update();
		}
	}
}
