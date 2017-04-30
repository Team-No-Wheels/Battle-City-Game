#include "Pch.h"
#include "ActionFreeze.h"
#include "BasicTankAI.h"

namespace AnonymousEngine
{

	ATTRIBUTED_DEFINITIONS(ActionFreeze);

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
				uint32_t size = entities.Size();

				// Look For All Enemy Tanks
				for (uint32_t i = 0; i < size; ++i)
				{
					BasicTankAI* tank = entities.Get<Scope*>(i)->As<BasicTankAI>();

					if (tank != nullptr)
					{
						// Freeze Movement And Shooting
						if (mTimeRemaining > Zero)
						{
							tank->Freeze();
						}

						// Unfreeze Tank
						else
						{
							tank->Unfreeze();
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

	void ActionFreeze::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	ACTION_FACTORY_DEFINITIONS(ActionFreeze);
}
