#include "Pch.h"
#include "BasicTankAI.h"
#include "RandomNumbersGenerator.h"

using namespace std;
using namespace chrono;

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(BasicTankAI);
	ENTITY_FACTORY_DEFINITIONS(BasicTankAI);

	/************************************************************************/
	const float BasicTankAI::DEFAULT_SPEED = 1.0f;
	const int32_t BasicTankAI::DEFAULT_BULLETS_NUM = 1;
	const int32_t BasicTankAI::DEFAULT_ARMOR = 1;
	const uint32_t BasicTankAI::DEFAULT_PROB_TO_SHOOT_IN_MOV = 10;
	const uint32_t BasicTankAI::DEFAULT_PROB_TO_SHOOT_IN_COL_PLAYER = 70;
	const uint32_t BasicTankAI::DEFAULT_PROB_TO_SHOOT_IN_COL_WALL = 50;
	const int32_t BasicTankAI::MAX_PROB = 100;
	const milliseconds BasicTankAI::DEFAULT_SHOT_COOLDOWN_TIME = seconds(1);

	/************************************************************************/
	BasicTankAI::BasicTankAI(const float speed, const int32_t bulletsNum, const int32_t armor, const uint32_t probToShootInMov) :
		mSpeed(speed), mBulletsNum(bulletsNum), mArmor(armor), mProbToShootWhileMoving(probToShootInMov), 
		mCurrentState(State::Idle), mShotCooldownTimer(DEFAULT_SHOT_COOLDOWN_TIME)
	{
		mMoveComponent->SetSpeed(mSpeed);
		mMoveComponent->SetDirection(ActionMove::Direction::Down);
		mShootComponent->SetCapacityToShoot(mBulletsNum);
	}

	/************************************************************************/
	void BasicTankAI::Update(WorldState& worldState)
	{
		TankBase::Update(worldState);
		worldState.mEntity = this;

		State previousState = mCurrentState;
		switch (previousState)
		{
			case State::Idle:
				DecideNextDestination();
				break;

			case State::Moving:
				if (mShotCooldownTimer > milliseconds::zero())
				{
					mShotCooldownTimer -= worldState.mGameTime.ElapsedGameTime();
				}
				else
				{
					TryToShoot(mProbToShootWhileMoving);
					mShotCooldownTimer = DEFAULT_SHOT_COOLDOWN_TIME;
				}
				// todo movement logic here
				break;

			case State::Frozen:
				// do nothing
				break;

			default:;
		}

		worldState.mEntity = nullptr;

	}

	/************************************************************************/
	void BasicTankAI::OnCollision()
	{
		// todo depending on the type of collision(tag of the collider of the go passed), we either decrement armor if bullet
		// decide to go idle if it's unbreakable wall, decide to go idle or shoot(50% ~ 70%) if it's brick or flag, or shoot if it's the player
	}

	/************************************************************************/
	void BasicTankAI::Freeze()
	{
		mCurrentState = State::Frozen;
	}

	/************************************************************************/
	void BasicTankAI::Unfreeze()
	{
		mCurrentState = State::Idle;
	}

	/************************************************************************/
	void BasicTankAI::AppendPrescribedAttributeNames(Vector<string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	/************************************************************************/
	void BasicTankAI::TryToShoot(const uint32_t probability) const
	{
		auto prob = RandomNumbersGenerator::GetInstance().GetRangedRandom(MAX_PROB);
		if (prob <= static_cast<int32_t>(probability) && mShootComponent->CanShoot())
		{
			mShootComponent->CreateBullet();
		}
	}

}
