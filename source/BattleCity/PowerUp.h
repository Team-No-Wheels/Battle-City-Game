#pragma once
#include "GameObject.h"
#include "EventSubscriber.h"
#include "Event.h"
#include "MessageCollision.h"
#include "EventMessageAttributed.h"
#include "TankPlayer.h"
#include "Sector.h"
#include "WorldState.h"
#include "EventQueue.h"
#include "World.h"
#include "WorldState.h"
#include "PowerUpSpawner.h"

namespace AnonymousEngine
{
	using namespace Containers;
	using namespace Core;

	class PowerUpSpawner;

	class PowerUp : public GameObject
	{
		ATTRIBUTED_DECLARATIONS(PowerUp, GameObject);

	public:

		enum class PowerUpType
		{
			Unknown = 0,
			Tank, // Extra Life
			Clock, // Freeze Enemies
			Shield, // Invincibility
			Bomb, // Destroy Visible Enemies
			Star, // 1 = faster bullets, 2 = double shot, 3 = destroy steel walls
			Shovel, // Steel Wall Around Base
			MaxTypes
		};

		PowerUp();
		~PowerUp() = default;

		void SetType(PowerUpType newType);
		void Activate(TankPlayer& player, Containers::WorldState& worldState);
		void Update(WorldState& worldState) override;
		void OnCollision(GameObject& otherGameObject) override;
		void SetSpawner(PowerUpSpawner& spawner);

	private:
		typedef std::pair<Entity*, Entity*> CollisionPair;
		PowerUpType mType;
		PowerUpSpawner* mSpawner;

		void ActivateTank(Containers::WorldState& worldState);
		void ActivateClock(Containers::WorldState& worldState);
		void ActivateShield(TankPlayer& player);
		void ActivateBomb(TankPlayer& player, Containers::WorldState& worldState);
		void ActivateShovel();
		void ActivateStar(TankPlayer& player);

		WorldState* FindWorldState();

		static const std::string mPowerupKey;
	};

	ENTITY_FACTORY_DECLARATIONS(PowerUp);
}
