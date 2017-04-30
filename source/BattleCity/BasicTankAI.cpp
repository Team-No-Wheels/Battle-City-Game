#include "Pch.h"
#include "BasicTankAI.h"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(BasicTankAI);
	ENTITY_FACTORY_DEFINITIONS(BasicTankAI);

	/************************************************************************/
	const float BasicTankAI::DEFAULT_SPEED = 1.0f;
	const int32_t BasicTankAI::DEFAULT_BULLETS_NUM = 1;
	const int32_t BasicTankAI::DEFAULT_ARMOR = 1;

	/************************************************************************/
	BasicTankAI::BasicTankAI(const float speed, const int32_t bulletsNum, const int32_t armor) :
		mIsFrozen(false), mCurrentState(State::Idle), mSpeed(speed), mBulletsNum(bulletsNum), mArmor(armor)
	{
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

				break;

			default:;
		}

		worldState.mEntity = nullptr;

	}

	/************************************************************************/
	void BasicTankAI::Freeze()
	{
		mIsFrozen = true;
	}

	/************************************************************************/
	void BasicTankAI::Unfreeze()
	{
		mIsFrozen = false;
	}

	void BasicTankAI::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

}
