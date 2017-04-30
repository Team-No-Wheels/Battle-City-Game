#include "Pch.h"
#include "PowerUp.h"
#include "Event.h"
#include "ScoreMessageStructs.h"

namespace AnonymousEngine
{
	const std::string PowerUp::mPowerupKey = "PowerUps";

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

	void PowerUp::Activate(TankPlayer& player, Containers::WorldState& worldState)
	{
		//The player receives a score for picking up a power up.
		ScoreEventMessage scoreMessage(mPowerupKey, worldState);
		const std::shared_ptr<Core::Event<ScoreEventMessage>> eventptr = std::make_shared<Core::Event<ScoreEventMessage>>(scoreMessage);
		worldState.mWorld->EventQueue().Enqueue(eventptr, worldState.mGameTime, 0u);

		switch (mType)
		{
		case PowerUpType::Tank:
			ActivateTank(worldState);
			break;

		case PowerUpType::Clock:
			ActivateClock();
			break;

		case PowerUpType::Shield:
			ActivateShield(player);
			break;

		case PowerUpType::Bomb:
			ActivateBomb(player, worldState);
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
					Activate(*player, message->WorldState());
					break;
				}
			}
		}
	}

	void PowerUp::ActivateTank(Containers::WorldState& worldState)
	{
		PlayerSideHealMessage healMessage(worldState);
		const std::shared_ptr<Core::Event<PlayerSideHealMessage>> eventptr = std::make_shared<Core::Event<PlayerSideHealMessage>>(healMessage);
		worldState.mWorld->EventQueue().Enqueue(eventptr, worldState.mGameTime, 0u);
	}

	void PowerUp::ActivateClock()
	{
		mClockActivated = true;
	}

	void PowerUp::ActivateShield(TankPlayer& player)
	{
		player.SetInvincibility(true);
	}

	void PowerUp::ActivateBomb(TankPlayer& player, Containers::WorldState& worldState)
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

					// Tell score manager that a tank was destroyed
					TankDestroyedNoScoreMessage message(worldState);
					const std::shared_ptr<Core::Event<TankDestroyedNoScoreMessage>> eventptr = std::make_shared<Core::Event<TankDestroyedNoScoreMessage>>(message);
					worldState.mWorld->EventQueue().Enqueue(eventptr, worldState.mGameTime, 0u);
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
