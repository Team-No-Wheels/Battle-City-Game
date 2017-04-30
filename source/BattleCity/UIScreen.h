#pragma once

#include "Factory.h"
#include "Entity.h"

namespace BattleCity
{
	class UIScreen : public AnonymousEngine::Containers::Entity
	{
	public:
		/** Initialize UI screen
		 */
		UIScreen() = default;

		/** Destroy and free up resources used by this screen
		 */
		virtual ~UIScreen() = default;

		/** Update UI state and rendering
		 */
		virtual void Update();

		ATTRIBUTED_DECLARATIONS(UIScreen, AnonymousEngine::Containers::Entity);
	};

	CONCRETE_FACTORY_DECLARATIONS(UIScreen, UIScreen);
}
