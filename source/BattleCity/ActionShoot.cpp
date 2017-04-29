#include "Pch.h"
#include "ActionShoot.h"
#include "TankPlayer.h"

using namespace AnonymousEngine;
RTTI_DEFINITIONS(ActionShoot);

ActionShoot::ActionShoot() :
	mCanShoot(true), mIsEnemy(true), mBulletsLiving(3), mBulletsPending(3),
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
	if (mBulletsPending.Size() != 0)
	{
		DestroyBullet();
	}
}

void ActionShoot::CreateBullet()
{
	Bullet* curBullet =  Factory<Entity>::Create(std::string("Bullet"))->As<Bullet>();

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

	// Set Bullet Speed
	if(isFast);
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

void ActionShoot::Notify(class EventPublisher& publisher)
{
	Event<MessageInput>* curEvent = publisher.As<Event<MessageInput>>();

	if (curEvent != nullptr)
	{
		MessageInput* message = &const_cast<MessageInput&>(curEvent->Message());
		Vector<std::string*>* Keys = &message->GetKeys();

		for (std::string* c : *Keys)
		{
			// Create Bullet If Shooting Key Is Pressed
			if (*c == "Shoot" && mCanShoot)
			{
				CreateBullet();

				// Delay Creation Of 2nd Bullet For Double Shot
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
	if(mBulletsLiving.Size() == 0)
	{
		mCanShoot = true;
	}
	
}