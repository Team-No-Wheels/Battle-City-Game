#include "Pch.h"
#include "PowerUp.h"
#include "Event.h"
#include "ScoreMessageStructs.h"

namespace AnonymousEngine
{
	const std::string PowerUp::mPowerupKey = "PowerUps";

	ATTRIBUTED_DEFINITIONS(PowerUp);

	PowerUp::PowerUp() :
		mType(PowerUpType::Tank)
	{
		GetCollider().SetTag(AnonymousEngine::Core::Collider::ColliderTag::PowerUp);
	}

	void PowerUp::SetType(PowerUpType newType)
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
			ActivateClock(worldState);
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

		worldState.mEntity = nullptr;
	}

	void PowerUp::OnCollision(GameObject& otherGameObject)
	{
		TankPlayer* player = otherGameObject.As<TankPlayer>();
		if (player != nullptr)
		{
			Activate(*player, *FindWorldState());
		}
	}

	void PowerUp::ActivateTank(Containers::WorldState& worldState)
	{
		PlayerSideHealMessage healMessage(worldState);
		const std::shared_ptr<Core::Event<PlayerSideHealMessage>> eventptr = std::make_shared<Core::Event<PlayerSideHealMessage>>(healMessage);
		worldState.mWorld->EventQueue().Enqueue(eventptr, worldState.mGameTime, 0u);
	}

	void PowerUp::ActivateClock(Containers::WorldState& worldState)
	{
		EventMessageAttributed msg;
		msg.SetSubtype("Freeze");
		msg.SetWorld(*worldState.mWorld);
		worldState.mWorld->EventQueue().Enqueue(std::make_shared<Event<EventMessageAttributed>>(Event<EventMessageAttributed>(msg)), worldState.mGameTime, 0U);
	}

	void PowerUp::ActivateShield(TankPlayer& player)
	{
		player.SetInvincibility(false);
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
				TankBase* tank = entities.Get<Scope>(i).As<TankBase>();

				if (tank != nullptr)
				{
					tank->SetMarkForDelete();

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
		// TODO Implement
	}

	void PowerUp::ActivateStar(TankPlayer& player)
	{
		player.IncrementStars();
	}

	WorldState* PowerUp::FindWorldState()
	{
		WorldState* state = nullptr;
		Scope* curScope = GetParent();

		// Loop Through Parent To Find World
		while (curScope->GetParent() != nullptr)
		{
			curScope = curScope->GetParent();

			// If World, Return WorldState
			if (curScope->Is(World::TypeIdClass()))
			{
				state = &curScope->As<World>()->GetWorldState();
			}
		}

		return state;
	}

	void PowerUp::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	ENTITY_FACTORY_DEFINITIONS(PowerUp);
}
