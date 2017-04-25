#include "Pch.h"
#include "ActionShoot.h"
#include "TankPlayer.h"

// TODO : If Player, Allow Double Shots, Faster Shots, Ability To Destroy Steel Blocks When 

using namespace AnonymousEngine;
RTTI_DEFINITIONS(ActionShoot);

ActionShoot::ActionShoot() :
	mCanShoot(true), mTimeLastShot(0), mShootFrequency(100), mIsEnemy(true),
	mBulletPendingKill(false), mCurBullet(nullptr)
{
	if (GetParent()->Is(TankPlayer::TypeIdClass()))
	{
		mIsEnemy = false;
		Event<MessageInput>::Subscribe(*this);
	}
}

ActionShoot::~ActionShoot()
{
	Event<MessageInput>::Unsubscribe(*this);
}

void ActionShoot::Update(WorldState& worldState)
{
	mTimeLastShot += worldState.mGameTime.ElapsedGameTime();

	if (mBulletPendingKill && mCurBullet != nullptr)
	{
		DestroyBullet();
	}

	if (mCanShoot && mTimeLastShot > mShootFrequency)
	{
		CreateBullet();
	}
}

void ActionShoot::CreateBullet()
{
	mCurBullet =  Factory<Entity>::Create(std::string("Bullet"))->As<Bullet>();
	mCurBullet->SetShootParent(*this);
	mCanShoot = false;
}

void ActionShoot::Notify(class EventPublisher& publisher)
{
	Event<MessageInput>* curEvent = publisher.As<Event<MessageInput>>();

	if (curEvent != nullptr && mCanShoot)
	{
		MessageInput* message = &const_cast<MessageInput&>(curEvent->Message());
		Vector<std::string*>* Keys = &message->GetKeys();

		for (std::string* c : *Keys)
		{
			if (*c == "Shoot")
			{
				CreateBullet();
				break;
			}
		}
	}
}

void ActionShoot::PendKillBullet()
{
	mBulletPendingKill = true;
}

void ActionShoot::DestroyBullet()
{
	mCanShoot = true;
	mBulletPendingKill = false;
	mTimeLastShot = std::chrono::duration<int>(0);
	delete mCurBullet;
}