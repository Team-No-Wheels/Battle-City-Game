#pragma once

#include "HashMap.h"
#include "UIScreen.h"
#include "Entity.h"

namespace BattleCity
{
	class UIManager final
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
		UIManager() = default;
		/** Destroys the UI manager
		 */
		~UIManager() = default;

		/** Activate a UI screen
		 *  @param uiType The UI screen to activate
		 */
		void ActivateUiScreen(UiType uiType);

		/** Deactivate a UI screen
		 *  @param uiType The UI screen to deactivate
		 */
		void DeactivateUiScreen(UiType uiType);
		
		/** Updates the active UI screebs
		 */
		void Update();

	private:

		// stores the active screens
		AnonymousEngine::HashMap<UiType, UIScreen*> mActiveUiScreens;

		static AnonymousEngine::HashMap<UiType, std::string> ScreenClassNames;
	};
}
