#pragma once

#include "UIScreen.h"

namespace BattleCity
{
	class MainMenuScreen final : public UIScreen
	{
	public:
		/** The options in the menu
		 */
		enum MenuOptions
		{
			Invalid,
			StartGame,
			Exit,
			MaxOptions
		};

		/** Initialize the menu
		 */
		MainMenuScreen();

		/** Update menu state
		 *  @param worldState The current world state
		 */
		void Update(AnonymousEngine::Containers::WorldState& worldState) override;
	private:
		// Currently selected option
		MenuOptions mCurrentOption;

		ATTRIBUTED_DECLARATIONS(MainMenuScreen, UIScreen);
	};

	CONCRETE_FACTORY_DECLARATIONS(UIScreen, MainMenuScreen);
}
