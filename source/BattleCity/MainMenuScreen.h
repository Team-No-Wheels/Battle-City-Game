#pragma once

#include <cstdint>
#include "UIScreen.h"

namespace BattleCity
{
	class MainMenuScreen final : public UIScreen
	{
	public:
		MainMenuScreen();
		void Update() override;
	private:
		std::uint32_t mCurrentOption;
	};

	CONCRETE_FACTORY_DECLARATIONS(UIScreen, MainMenuScreen);
}
