#pragma once
#include "MessageInput.h"
#include "Action.h"
#include "Factory.h"
#include "RandomNumbersGenerator.h"
#include "Vector.h"

namespace AnonymousEngine
{

	using namespace Containers;
	//using namespace Core;

	class PowerUp;

	class PowerUpSpawner : public Action
	{

		ATTRIBUTED_DECLARATIONS(PowerUpSpawner, Action);

	public:

		PowerUpSpawner();
		~PowerUpSpawner();

		void Update(WorldState& worldState) override;

		/* Spawn a power up, push a pointer to it to a vector, and set its type & position
		*/
		void SpawnPowerUp();

		/* Called From PowerUp entity after activation, mark that power up as ready to delete
		*/
		void PendKillPowerUp(PowerUp& power);

		/* Destroy any powers ups pending deletion
		*/
		void DestroyPowerUps();

	private:

		std::chrono::milliseconds LastSpawned, SpawnFrequency;
		Vector<PowerUp*> mPowersLiving;
		Vector<PowerUp*> mPowersPending;
	};

	ACTION_FACTORY_DECLARATIONS(PowerUpSpawner);
}

