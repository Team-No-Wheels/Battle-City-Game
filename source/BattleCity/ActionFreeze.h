#pragma once
#include "EventSubscriber.h"
#include "Event.h"
#include "Action.h"
#include "Sector.h"
#include "TankBase.h"

namespace AnonymousEngine
{
	using namespace Containers;
	using namespace Core;

	class ActionFreeze final : public Action, public EventSubscriber
	{

		ATTRIBUTED_DECLARATIONS(ActionFreeze, Action);

	public:

		ActionFreeze();
		~ActionFreeze();

		void Update(WorldState& worldState) override;
		void Notify(class EventPublisher& publisher) override;

	private:

		std::chrono::milliseconds mTimeFrozen, mTimeRemaining, Zero;
		bool mFreezeCalled;
	};

	ACTION_FACTORY_DECLARATIONS(ActionFreeze);
}
