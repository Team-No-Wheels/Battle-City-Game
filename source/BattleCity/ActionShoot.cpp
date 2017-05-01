#include "Pch.h"
#include "ActionShoot.h"
#include "TankPlayer.h"
#include "Bullet.h"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(ActionShoot);

	ActionShoot::ActionShoot(bool isPlayer) :
		mBulletsCapacity(1), mIsFast(false), mIsStrong(false), mIsOwnedByPlayer(isPlayer), mBulletsLiving(3)
	{
	}

	void ActionShoot::Update(WorldState& worldState)
	{
		worldState.mAction = this;

		worldState.mAction = nullptr;
	}

	void ActionShoot::CreateBullet()
	{
		Bullet* curBullet = new Bullet(this);

		//Store Reference To Bullet
		mBulletsLiving.PushBack(curBullet);

		//Get A Reference To Bullet MoveComponent And Parent
		TankBase* tank = GetParent()->As<TankBase>();
		ActionMove* moveComponent = &curBullet->GetMoveComponent();

		// Set Direction Of Bullet
		if (tank != nullptr)
			moveComponent->SetDirection(tank->MoveComponent().GetDirection());
		else
			moveComponent->SetDirection(ActionMove::Direction::Up);

		if (mIsFast)
		{
			moveComponent->SetSpeed(2 * moveComponent->sDefaultSpeed);
		}

		// set the tag for the bullet
		if (mIsOwnedByPlayer)
		{
			curBullet->GetCollider().SetTag(Collider::ColliderTag::PlayerBullet);
		}
		else
		{
			curBullet->GetCollider().SetTag(Collider::ColliderTag::EnemyBullet);
		}
	}

	void ActionShoot::KillBullet(Bullet& bullet)
	{
		// Move Bullet To PendingKill Vector (Gets Destroyed Next Update)
		mBulletsLiving.Remove(&bullet);
		bullet.SetMarkForDelete();
	}

	bool ActionShoot::CanShoot() const
	{
		return mBulletsLiving.Size() < mBulletsCapacity;
	}

	bool ActionShoot::IsOwnedByPlayer() const
	{
		return mIsOwnedByPlayer;
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
