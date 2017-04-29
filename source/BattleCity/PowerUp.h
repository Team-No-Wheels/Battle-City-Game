#pragma once
#include "Entity.h"
#include "EventSubscriber.h"
#include "Event.h"
#include "MessageCollision.h"
#include "EventMessageAttributed.h"
#include "TankPlayer.h"
#include "Sector.h"
#include "WorldState.h"
#include "EventQueue.h"
#include "World.h"

namespace AnonymousEngine
{
	using namespace Containers;
	using namespace Core;

	class PowerUp : public Entity, public EventSubscriber
	{

		RTTI_DECLARATIONS(PowerUp, Entity);

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
		~PowerUp();

		void setType(PowerUpType newType);
		void Activate(TankPlayer& player);
		void Update(WorldState& worldState) override;
		void Notify(class EventPublisher& publisher);

	private:
		typedef std::pair<Entity*, Entity*> CollisionPair;
		PowerUpType mType;
		bool mClockActivated;

		void ActivateTank(TankPlayer& player);
		void ActivateClock();
		void ActivateShield(TankPlayer& player);
		void ActivateBomb(TankPlayer& player);
		void ActivateShovel();
		void ActivateStar(TankPlayer& player);

	};

	ENTITY_FACTORY_DECLARATIONS(PowerUp);
	ENTITY_FACTORY_DEFINITIONS(PowerUp);
}
