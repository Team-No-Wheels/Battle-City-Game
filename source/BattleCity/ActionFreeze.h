#pragma once
#include "EventSubscriber.h"
#include "EventMessageAttributed.h"
#include "Event.h"
#include "Action.h"
#include "Sector.h"
#include "TankBase.h"

namespace AnonymousEngine
{
	using namespace Containers;
	using namespace Core;

	class ActionFreeze : public Action, public EventSubscriber
	{

		RTTI_DECLARATIONS(ActionFreeze, Action);

	public:

		ActionFreeze();
		~ActionFreeze();

		void Update(WorldState& worldState);
		void Notify(class EventPublisher& publisher);

	private:

		std::chrono::milliseconds mTimeFrozen, mTimeRemaining, Zero;

	};

	ACTION_FACTORY_DECLARATIONS(ActionFreeze);
	ACTION_FACTORY_DEFINITIONS(ActionFreeze);
}
