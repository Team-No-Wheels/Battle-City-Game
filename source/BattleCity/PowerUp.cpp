#include "Pch.h"
#include "PowerUp.h"

/* TO DO
ActivateCLock() -  All Of It
ActivateShovel() - All Of It
ActivateBomb() - Change TankBase To Enemy, Destroy Enemy
*/

using namespace AnonymousEngine;
RTTI_DEFINITIONS(PowerUp);

PowerUp::PowerUp() :
	mType(PowerUpType::Unknown)
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
	case PowerUpType::Tank :
		ActivateTank(player);
		break;

	case PowerUpType::Clock :
		ActivateClock();
		break;

	case PowerUpType::Shield :
		ActivateShield(player);
		break;

	case PowerUpType::Bomb:
		ActivateBomb();
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
	
}

void PowerUp::ActivateShield(TankPlayer& player)
{
	player.SetInvincibility(true);
}

void PowerUp::ActivateBomb()
{
	Sector* sector = GetParent()->As<Sector>();

	if (sector != nullptr)
	{
		Datum& entities = sector->Entities();

		std::uint32_t size = entities.Size();
		for (std::uint32_t i = 0; i < size; ++i)
		{
			//TODO: Change TankBase To Enemy Class Type
			TankBase* enemy = entities.Get<Scope*>(i)->As<TankBase>();

			if (enemy != nullptr)
			{
				//DESTROY TANK
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