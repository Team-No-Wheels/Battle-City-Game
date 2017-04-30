#pragma once

namespace BattleCity
{
	class UIManager
	{
	public:
		UIManager();
		~UIManager();

		void MainMenu();
		void PauseMenu();
		void LevelTransitionUI();
		void LevelCompletionUI();
		void UpdateLevelUI();
	};
}
