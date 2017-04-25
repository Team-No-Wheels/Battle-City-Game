#include "Pch.h"
#include "Bullet.h"
#include "TankPlayer.h"

using namespace AnonymousEngine;
RTTI_DEFINITIONS(Bullet);

Bullet::Bullet() :
	mMoveComponent(CreateAction("MovementComponent", "ActionMove").As<ActionMove>()),
	mShootParent(nullptr), isStrong(false)
{
	Event<MessageCollision>::Subscribe(*this);
}

Bullet::Bullet( ActionShoot& parent) :
	mMoveComponent(CreateAction("MovementComponent", "ActionMove").As<ActionMove>()),
	mShootParent(&parent)
{
	Event<MessageCollision>::Subscribe(*this);
}

Bullet::~Bullet()
{
	Event<MessageCollision>::Unsubscribe(*this);
	mShootParent = nullptr;
}

void Bullet::SetShootParent(ActionShoot& parent)
{
	mShootParent = &parent;
}

ActionMove& Bullet::MoveComponent()
{
	return *mMoveComponent;
}

void Bullet::Notify(class EventPublisher& publisher)
{
	Event<MessageCollision>* curEvent = publisher.As<Event<MessageCollision>>();

	if (curEvent != nullptr)
	{
		MessageCollision* message = const_cast<MessageCollision*>(&curEvent->Message());
		Vector<CollisionPair>* entities = &message->GetEntities();

		for (CollisionPair e : *entities)
		{
			// Check If Player
			TankPlayer* player = e.first->As<TankPlayer>();
			if (player == nullptr)
			{
				player = e.second->As<TankPlayer>();
			}

			// Check If Bullet
			Bullet* bullet = e.first->As<Bullet>();
			if (bullet == nullptr)
			{
				bullet = e.second->As<Bullet>();
			}

			// Try Executing Actions If This Bullet Exists In List
			if (bullet != nullptr && bullet == this)
			{
				// Do Stuff If Player
				if (player != nullptr && !player->IsInvincible())
				{
					player->DecrementLives();
				}

				// Do Stuff If Enemy
				// Do Stuff If Wall

				mShootParent->PendKillBullet(*this);
			}
		}
	}

}
