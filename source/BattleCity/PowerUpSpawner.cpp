#include "Pch.h"
#include "PowerUpSpawner.h"
#include "PowerUp.h"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(PowerUpSpawner);

	PowerUpSpawner::PowerUpSpawner() :
		LastSpawned(0), SpawnFrequency(std::chrono::duration<int>(10)), 
		mPowersLiving(5), mPowersPending(5)
	{

	}

	PowerUpSpawner::~PowerUpSpawner()
	{
		DestroyPowerUps();
	}

	void PowerUpSpawner::Update(WorldState& worldState)
	{
		worldState.mAction = this->As<Action>();

		LastSpawned += worldState.mGameTime.ElapsedGameTime();

		// Wait X Seconds Before Spawning Another PowerUp
		if (LastSpawned > SpawnFrequency)
		{
			int spawnChance = rand() % 100;

			// After Enough Time, Each Update Has A 5% Chance To Spawn A PowerUp
			if (spawnChance <= 5)
			{
				SpawnPowerUp();
				LastSpawned = std::chrono::duration<int>(0);
			}
		}

		// Destroy PowerUps Pending To Be Killed
		if (mPowersPending.Size() > 0)
		{
			DestroyPowerUps();
		}

		worldState.mAction = nullptr;
	}

	void PowerUpSpawner::SpawnPowerUp()
	{
		// Spawn PowerUp
		PowerUp* power = Factory<Entity>::Create("PowerUp")->As<PowerUp>();
		power->SetSpawner(*this);

		// Set Type
		int type = (rand() % 6) + 1;
		power->SetType((PowerUp::PowerUpType)type);
		
		// Set Position
		RandomNumbersGenerator& generator = RandomNumbersGenerator::GetInstance();
		glm::vec4 position;
		position.x = (float)generator.GetRangedRandom(4, 252);
		position.y = (float)generator.GetRangedRandom(4, 236);
		position.z = 0;
		position.w = 0;
		power->SetPosition(position);
	}

	void PowerUpSpawner::PendKillPowerUp(PowerUp& power)
	{
		mPowersLiving.Remove(&power);
		mPowersPending.PushBack(&power);
	}

	void PowerUpSpawner::DestroyPowerUps()
	{
		for (std::uint32_t i = 0; i < mPowersPending.Size(); i++)
		{
			delete mPowersPending[i];
		}

		mPowersPending.Clear();
	}

	void ActionShoot::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	ACTION_FACTORY_DEFINITIONS(PowerUpSpawner);
}
