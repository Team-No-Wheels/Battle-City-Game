#pragma once

#include "TankBase.h"
#include "ActionFreeze.h"

namespace AnonymousEngine
{
	/** This class represents the base for all of the Tank AIs.
	*/
	class BasicTankAI : public TankBase
	{
		ATTRIBUTED_DECLARATIONS(BasicTankAI, TankBase);

	public:

		/** Enumeration representing the Tank AI State.
		*/
		enum class State
		{
			Idle,
			Moving,
			Frozen
		};

		/** BasicTankAI constructor.
		*/
		BasicTankAI(const float speed = DEFAULT_SPEED, const int32_t bulletsNum = DEFAULT_BULLETS_NUM, 
					const int32_t armor = DEFAULT_ARMOR, const uint32_t probToShootInMov = DEFAULT_PROB_TO_SHOOT_IN_MOV);

		/** BasicTankAI destructor.
		*/
		virtual ~BasicTankAI() = default;

		// delete copy semantics
		BasicTankAI(const BasicTankAI & rhs) = delete;
		BasicTankAI& operator=(const BasicTankAI& rhs) = delete;

		/** Update method of the Basic TankAI.
		* @param worldState: The current World state.
		* @see WorldState
		*/
		virtual void Update(WorldState& worldState) override;

		/** Handles collision event for the TankAI.
		*/
		void OnCollision() /*override*/;

		/** Freezes the TankAI and stops it from doing anything.
		*/
		void Freeze();

		/** Unfreezes the TankAI.
		*/
		void Unfreeze();

	protected:

		float mSpeed;
		int32_t mBulletsNum;
		int32_t mArmor;
		uint32_t mProbToShootWhileMoving;

	private:

		ActionFreeze mActionFreeze;
		State mCurrentState;

		std::chrono::milliseconds mShotCooldownTimer;

		static const float DEFAULT_SPEED;
		static const int32_t DEFAULT_BULLETS_NUM;
		static const int32_t DEFAULT_ARMOR;
		static const uint32_t DEFAULT_PROB_TO_SHOOT_IN_MOV;
		static const uint32_t DEFAULT_PROB_TO_SHOOT_IN_COL_PLAYER;
		static const uint32_t DEFAULT_PROB_TO_SHOOT_IN_COL_WALL;
		static const int32_t MAX_PROB;
		static const std::chrono::milliseconds DEFAULT_SHOT_COOLDOWN_TIME;

		// map
		// nextDestination
		void DecideNextDestination();
		void TryToShoot(const uint32_t probability) const;

	};

	ENTITY_FACTORY_DECLARATIONS(BasicTankAI);
}
