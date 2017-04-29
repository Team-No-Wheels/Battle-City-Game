#include "Pch.h"
#include "PowerUp.h"

namespace AnonymousEngine
{

	RTTI_DEFINITIONS(PowerUp);

	PowerUp::PowerUp() :
		mType(PowerUpType::Tank), mClockActivated(false)
	{

	}

	PowerUp::~PowerUp()
	{

	}

	void PowerUp::setType(PowerUpType newType)
	{
		mType = newType;
	}

	void PowerUp::Activate(TankPlayer& player)
	{

		switch (mType)
		{
		case PowerUpType::Tank:
			ActivateTank(player);
			break;

		case PowerUpType::Clock:
			ActivateClock();
			break;

		case PowerUpType::Shield:
			ActivateShield(player);
			break;

		case PowerUpType::Bomb:
			ActivateBomb(player);
			break;

		case PowerUpType::Shovel:
			ActivateShovel();
			break;

		case PowerUpType::Star:
			ActivateStar(player);
			break;

		default:
			break;
		}
	}

	void PowerUp::Update(WorldState& worldState)
	{
		worldState.mEntity = this;

		if (mClockActivated)
		{
			mClockActivated = false;
			EventQueue* mEventQueue = &worldState.mWorld->EventQueue();
			EventMessageAttributed msg;
			msg.SetSubtype("Freeze");
			msg.SetWorld(*worldState.mWorld);
			mEventQueue->Enqueue(std::make_shared<Event<EventMessageAttributed>>(Event<EventMessageAttributed>(msg)), worldState.mGameTime, 0U);
		}

		worldState.mEntity = nullptr;
	}

	void PowerUp::Notify(class EventPublisher& publisher)
	{
		Event<MessageCollision>* curEvent = publisher.As<Event<MessageCollision>>();

		if (curEvent != nullptr)
		{
			MessageCollision* message = const_cast<MessageCollision*>(&curEvent->Message());
			Vector<CollisionPair>* entities = &message->GetEntities();

			for (CollisionPair e : *entities)
			{
				// Check Player
				TankPlayer* player = e.first->As<TankPlayer>();
				if (player == nullptr)
				{
					player = e.second->As<TankPlayer>();
				}

				// Check PowerUp
				PowerUp* power = e.first->As<PowerUp>();
				if (power == nullptr)
				{
					power = e.second->As<PowerUp>();
				}

				// Activate If Player Collided With This PowerUp
				if (player != nullptr && power != nullptr && power == this)
				{
					Activate(*player);
					break;
				}
			}
		}
	}

	void PowerUp::ActivateTank(TankPlayer& player)
	{
		player.IncrementLives();
	}

	void PowerUp::ActivateClock()
	{
		mClockActivated = true;
	}

	void PowerUp::ActivateShield(TankPlayer& player)
	{
		player.SetInvincibility(true);
	}

	void PowerUp::ActivateBomb(TankPlayer& player)
	{
		Sector* curSector = &player.GetSector();

		if (curSector != nullptr)
		{
			Datum& entities = curSector->Entities();
			std::uint32_t size = entities.Size();

			for (std::uint32_t i = 0; i < size; ++i)
			{
				TankBase* e = entities.Get<Scope*>(i)->As<TankBase>();

				if (e != nullptr)
				{
					// Destroy Enemy Tanks
				}
			}
		}
	}

	void PowerUp::ActivateShovel()
	{

	}

	void PowerUp::ActivateStar(TankPlayer& player)
	{
		player.IncrementStars();
	}

	ENTITY_FACTORY_DEFINITIONS(PowerUp);
}
