#pragma once

#include "Factory.h"

namespace BattleCity
{
	class UIScreen
	{
	public:
		UIScreen() = default;
		virtual ~UIScreen() = default;

		virtual void Update();
	};

	CONCRETE_FACTORY_DECLARATIONS(UIScreen, UIScreen);
}
