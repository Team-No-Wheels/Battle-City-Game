#pragma once

namespace BattleCity
{
	class UIManager
	{
	public:

		enum class UiType
		{
			MainMenu,
			LevelIntro,
			InGame,
			Pause,
			GameOver,
			LevelComplete
		};

		/** Initialize a UI manager
		 */
		UIManager();
		/** Destroys the UI manager
		 */
		~UIManager();

		/** Set active UI type
		 *  @param uiType The current UI type to set active
		 */
		void SetActiveUI(UiType uiType);
		
		/** Updates the active UI
		 */
		void Update();

	private:

		// The active UI
		UiType mActiveUI;
	};
}
