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
			// todo maybe add a delayed state, where the tank just stands there breifly
			Idle,
			Moving,
			Frozen
		};

		/** BasicTankAI constructor.
		*/
		BasicTankAI(const float speed, const int32_t bulletsNum, const int32_t armor, const uint32_t probToShootInMov);

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
		virtual void OnCollision(GameObject& otherGameObject) override;

		/** Gets the type name of the tank.
		 * This method is pure virtual and it needs to be extended by any derived class.
		 * @return String representing the type.
		 */
		virtual std::string GetTankType() = 0;

		/** Freezes the TankAI and stops it from doing anything.
		*/
		void Freeze();

		/** Unfreezes the TankAI.
		*/
		void Unfreeze();

		/** Decrements the tanks armor. If the armor reaches 0, the tank is destroyed.
		*/
		bool DecrementArmor();

	protected:

		float mSpeed;
		int32_t mBulletsNum;
		int32_t mArmor;
		uint32_t mProbToShootWhileMoving;

	private:

		ActionFreeze* mActionFreeze;
		State mCurrentState;

		std::chrono::milliseconds mShotCooldownTimer;
		std::chrono::milliseconds mMovingInSameDirectionTimer;

		static const uint32_t DEFAULT_PROB_TO_SHOOT_IN_COL_PLAYER;
		static const uint32_t DEFAULT_PROB_TO_SHOOT_IN_COL_WALL;
		static const int32_t MAX_PROB;
		static const std::chrono::milliseconds DEFAULT_SHOT_COOLDOWN_TIME;
		static const std::chrono::milliseconds MIN_TIME_IN_SAME_DIRECTION;
		static const std::chrono::milliseconds MAX_TIME_IN_SAME_DIRECTION;

		void HandleMovingState(const WorldState& worldState);

		// map
		// nextDestination
		void DecideNextDestination();

		// collision helper methods
		void HandleCollisionWithPlayer(const GameObject& gameObject);
		void HandleCollisionWithDestructable();
		void HandleCollisionWithUndestructable();

		void TryToShoot(const uint32_t probability) const;

	};
}
