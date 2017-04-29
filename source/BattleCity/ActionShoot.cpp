#include "Pch.h"
#include "ActionShoot.h"
#include "TankPlayer.h"

namespace AnonymousEngine
{
	RTTI_DEFINITIONS(ActionShoot);

	ActionShoot::ActionShoot() :
		mCanShoot(true), mBulletsLiving(3), mBulletsPending(3),
		isFast(false), isDouble(false), isStrong(false)
	{}

	ActionShoot::~ActionShoot()
	{}

	void ActionShoot::Update(WorldState& worldState)
	{
		worldState.mAction = this;

		if (mBulletsPending.Size() != 0)
		{
			DestroyBullet();
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

		if (isFast)
		{
			moveComponent->SetSpeed(2 * moveComponent->DEFAULTSPEED);
		}

		// Set Bullet To Destroy Steel BLocks
		if (isStrong)
		{
			curBullet->isStrong = true;
		}

		// Can't Create Another Bullet If This Bullet Exists
		mCanShoot = false;
	}

	void ActionShoot::PendKillBullet(Bullet& bullet)
	{
		// Move Bullet To PendingKill Vector (Gets Destroyed Next Update)
		mBulletsLiving.Remove(&bullet);
		mBulletsPending.PushBack(&bullet);
	}

	void ActionShoot::DestroyBullet()
	{
		// Destroy Pending Bullets
		for (std::uint32_t i = 0; i < mBulletsPending.Size(); ++i)
		{
			delete mBulletsPending[i];
		}

		mBulletsPending.Clear();

		// Enable Shooting If There Are No Existing Bullets Left
		if (mBulletsLiving.Size() == 0)
		{
			mCanShoot = true;
		}

	}

	bool ActionShoot::CanShoot()
	{
		return mCanShoot;
	}

	bool ActionShoot::IsDouble()
	{
		return isDouble;
	}

	ACTION_FACTORY_DEFINITIONS(ActionShoot);
}
