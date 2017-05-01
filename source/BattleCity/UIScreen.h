#pragma once

#include "Factory.h"
#include "Entity.h"
#include "EventSubscriber.h"

namespace BattleCity
{
	class UIScreen : public AnonymousEngine::Containers::Entity, public AnonymousEngine::Core::EventSubscriber
	{
	public:
		/** Initialize UI screen
		 */
		UIScreen() = default;

		/** Destroy and free up resources used by this screen
		 */
		virtual ~UIScreen() = default;

		/** Update UI state and rendering
		 *  @param worldState The current world state
		 */
		void Update(AnonymousEngine::Containers::WorldState& worldState) override;

		/** Notify any events subscribed to
		 */
		void Notify(AnonymousEngine::Core::EventPublisher& publisher) override;

		ATTRIBUTED_DECLARATIONS(UIScreen, AnonymousEngine::Containers::Entity);
	};

	CONCRETE_FACTORY_DECLARATIONS(UIScreen, UIScreen);
	}
