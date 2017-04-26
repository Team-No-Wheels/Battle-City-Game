#include "Pch.h"
#include "ActionShoot.h"
#include "TankPlayer.h"

using namespace AnonymousEngine;
RTTI_DEFINITIONS(ActionShoot);

ActionShoot::ActionShoot() :
	mCanShoot(true), mTimeLastShot(0), mShootFrequency(100), mIsEnemy(true),
	mBulletPendingKill(false), mBulletsLiving(3), mBulletsPending(3),
	isFast(false), isDouble(false), isStrong(false)
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

	if (mBulletPendingKill)
	{
		DestroyBullet();
	}

	if (mCanShoot && mTimeLastShot > mShootFrequency)
	{
		CreateBullet();
		mTimeLastShot = std::chrono::milliseconds(0);
	}
}

void ActionShoot::CreateBullet()
{
	Bullet* curBullet =  Factory<Entity>::Create(std::string("Bullet"))->As<Bullet>();
	mBulletsLiving.PushBack(curBullet);

	curBullet->SetShootParent(*this);
	TankBase* tank = GetParent()->As<TankBase>();
	ActionMove* moveComponent = &curBullet->MoveComponent();

	if (tank != nullptr)
		moveComponent->SetDirection(tank->MoveComponent().GetDirection());
	else
		moveComponent->SetDirection(ActionMove::Direction::Up);

	if(isFast)
	{
		moveComponent->SetSpeed(2 * moveComponent->DEFAULTSPEED);
	}

	if (isStrong)
	{
		curBullet->isStrong = true;
	}

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
			if (*c == "Shoot" && mBulletsLiving.Size() > 0)
			{
				CreateBullet();

				if (isDouble)
				{
					std::async(std::launch::async, [this]()
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(10));
						CreateBullet();
					});
				}

				break;
			}
		}
	}
}

void ActionShoot::PendKillBullet(Bullet& bullet)
{
	mBulletPendingKill = true;
	mBulletsLiving.Remove(&bullet);
	mBulletsPending.PushBack(&bullet);
}

void ActionShoot::DestroyBullet()
{
	for (std::uint32_t i = 0; i < mBulletsPending.Size(); ++i)
	{
		delete mBulletsPending[i];
	}

	mBulletsPending.Clear();
	mBulletPendingKill = false;

	if(mBulletsLiving == 0)
	{
		mCanShoot = true;
		mTimeLastShot = std::chrono::duration<int>(0);
	}
	
}