#include "Pch.h"
#include "ActionShoot.h"
#include "TankPlayer.h"
#include "Bullet.h"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(ActionShoot);

	ActionShoot::ActionShoot(bool isPlayer) :
		mBulletsCapacity(1), mIsFast(false), mIsStrong(false), mBulletsLiving(3), mBulletsPending(3), mIsPlayer(isPlayer)
	{
	}

	void ActionShoot::Update(WorldState& worldState)
	{
		worldState.mAction = this;

		if (mBulletsPending.Size() != 0)
		{
			DestroyPendingBullets();
		}

		worldState.mAction = nullptr;
	}

	void ActionShoot::CreateBullet()
	{
		Bullet* curBullet = Factory<Entity>::Create(std::string("Bullet"))->As<Bullet>();

		//Store Reference To Bullet
		mBulletsLiving.PushBack(curBullet);
		curBullet->SetShootParent(*this);

		//Get A Reference To Bullet MoveComponent And Parent
		TankBase* tank = GetParent()->As<TankBase>();
		ActionMove* moveComponent = &curBullet->MoveComponent();

		// Set Direction Of Bullet
		if (tank != nullptr)
			moveComponent->SetDirection(tank->MoveComponent().GetDirection());
		else
			moveComponent->SetDirection(ActionMove::Direction::Up);

		if (mIsFast)
		{
			moveComponent->SetSpeed(2 * moveComponent->sDefaultSpeed);
		}
	}

	void ActionShoot::PendKillBullet(Bullet& bullet)
	{
		// Move Bullet To PendingKill Vector (Gets Destroyed Next Update)
		mBulletsLiving.Remove(&bullet);
		mBulletsPending.PushBack(&bullet);
	}

	void ActionShoot::DestroyPendingBullets()
	{
		// Destroy Pending Bullets
		for (std::uint32_t i = 0; i < mBulletsPending.Size(); ++i)
		{
			delete mBulletsPending[i];
		}

		mBulletsPending.Clear();
	}

	bool ActionShoot::CanShoot() const
	{
		return mBulletsLiving.Size() < mBulletsCapacity;
	}

	bool ActionShoot::IsPlayer() const
	{
		return mIsPlayer;
	}

	void ActionShoot::SetIsFast(const bool isFast)
	{
		mIsFast = isFast;
	}

	void ActionShoot::SetIsStrong(const bool isStrong)
	{
		mIsStrong = isStrong;
	}

	bool ActionShoot::IsStrong() const
	{
		return mIsStrong;
	}

	uint32_t ActionShoot::GetCapacityToShoot() const
	{
		return mBulletsCapacity;
	}

	void ActionShoot::SetCapacityToShoot(const uint32_t capacityToShoot)
	{
		mBulletsCapacity = capacityToShoot;
	}

	void ActionShoot::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}


	ACTION_FACTORY_DEFINITIONS(ActionShoot);
}
