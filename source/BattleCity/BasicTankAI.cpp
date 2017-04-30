#include "Pch.h"
#include "BasicTankAI.h"

namespace AnonymousEngine
{
	RTTI_DEFINITIONS(BasicTankAI);
	ENTITY_FACTORY_DEFINITIONS(BasicTankAI);

	/************************************************************************/
	const float BasicTankAI::DEFAULT_SPEED = 1.0f;
	const int32_t BasicTankAI::DEFAULT_BULLETS_NUM = 1;
	const int32_t BasicTankAI::DEFAULT_ARMOR = 1;

	/************************************************************************/
	BasicTankAI::BasicTankAI(const float speed, const int32_t bulletsNum, const int32_t armor):
		mIsFrozen(false), mSpeed(speed), mBulletsNum(bulletsNum), mArmor(armor)
	{
		Event<MessageCollision>::Subscribe(*this);
	}

	/************************************************************************/
	BasicTankAI::~BasicTankAI()
	{
		// todo unsubsccribe here
		Event<MessageCollision>::Unsubscribe(*this);
	}

	/************************************************************************/
	void BasicTankAI::Update(WorldState& worldState)
	{
		TankBase::Update(worldState);
		worldState.mEntity = this;

		// todo add logic here

		worldState.mEntity = nullptr;

	}

	/************************************************************************/
	void BasicTankAI::Notify(EventPublisher& publisher)
	{
		// todo handle collisions here
		
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
}
