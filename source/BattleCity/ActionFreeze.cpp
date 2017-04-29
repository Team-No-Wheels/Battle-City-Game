#include "Pch.h"
#include "ActionFreeze.h"

namespace AnonymousEngine
{

	RTTI_DEFINITIONS(ActionFreeze);

	ActionFreeze::ActionFreeze() :
		mTimeFrozen(10), mTimeRemaining(0), Zero(0)
	{
		Event<EventMessageAttributed>::Subscribe(*this);
	}

	ActionFreeze::~ActionFreeze()
	{
		Event<EventMessageAttributed>::Unsubscribe(*this);
	}

	void ActionFreeze::Update(WorldState& worldState)
	{
		worldState.mAction = this;

		if (mTimeRemaining > Zero)
		{
			mTimeRemaining -= worldState.mGameTime.ElapsedGameTime();
			Sector* curSector = worldState.mSector;

			if (curSector != nullptr)
			{
				Datum& entities = curSector->Entities();
				std::uint32_t size = entities.Size();

				// Look For All Enemy Tanks
				for (std::uint32_t i = 0; i < size; ++i)
				{
					TankBase* e = entities.Get<Scope*>(i)->As<TankBase>();

					if (e != nullptr)
					{
						// Freeze Movement And Shooting
						if (mTimeRemaining > Zero)
						{

						}

						// Unfreeze Tank
						else
						{

						}
					}
				}
			}
		}

		worldState.mAction = nullptr;
	}

	void ActionFreeze::Notify(class EventPublisher& publisher)
	{
		Event<EventMessageAttributed>* curEvent = publisher.As<Event<EventMessageAttributed>>();

		if (curEvent != nullptr)
		{
			EventMessageAttributed* message = const_cast<EventMessageAttributed*>(&curEvent->Message());

			if (message->GetSubtype() == "Freeze")
				mTimeRemaining = mTimeFrozen;
		}
	}

	ACTION_FACTORY_DEFINITIONS(ActionFreeze);
}
