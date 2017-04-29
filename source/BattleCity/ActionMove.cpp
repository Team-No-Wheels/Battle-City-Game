#include "Pch.h"
#include "ActionMove.h"
#include "TankPlayer.h"

using namespace AnonymousEngine;
RTTI_DEFINITIONS(ActionMove);

ActionMove::ActionMove() :
	mDirection(Direction::Up), mSpeed(1), mIsEnemy(true), mCanMove(true)
{
	if (GetParent()->Is(TankPlayer::TypeIdClass()))
	{
		mIsEnemy = false;
		Event<MessageInput>::Subscribe(*this);
	}
}

ActionMove::~ActionMove()
{
	if (!mIsEnemy)
	{
		Event<MessageInput>::Unsubscribe(*this);
	}
}

void ActionMove::Update(WorldState& worldState)
{
	worldState.mAction = this;

	// Automatically Move If Enemy. Enemy AI will change Speed/Direction
	if(mIsEnemy)
		Move();

	worldState.mAction = nullptr;
}

void ActionMove::Move()
{
	// Get A Reference To Parent As Entity
	Entity* entity = GetParent()->As<Entity>();

	if(entity != nullptr)
	{
		glm::vec2* position = &entity->GetPosition();

		// Update Position Based On Direction
		switch (mDirection)
		{
		case Direction::Up:
			position->y += mSpeed;
			break;

		case Direction::Down:
			position->y -= mSpeed;
			break;

		case Direction::Left:
			position->x -= mSpeed;
			break;

		case Direction::Right:
			position->x += mSpeed;
			break;

		default:
			break;
		}
	}

}

void ActionMove::SetSpeed(float speed)
{
	mSpeed = speed;
}

void ActionMove::SetDirection(Direction direction)
{
	mDirection = direction;
}

ActionMove::Direction ActionMove::GetDirection()
{
	return mDirection;
}

// For Player Only
void ActionMove::Notify(class EventPublisher& publisher)
{
	Event<MessageInput>* curEvent = publisher.As<Event<MessageInput>>();

	if (curEvent != nullptr)
	{
		MessageInput* message = &const_cast<MessageInput&>(curEvent->Message());
		Vector<std::string*>* Keys = &message->GetKeys();

		// Change Direction And Update Position If Movement Keys Pressed
		for (std::string* c : *Keys)
		{
			if (*c == "Up")
			{
				mDirection = Direction::Up;
				Move();
				break;
			}
			else if (*c == "Down")
			{
				mDirection = Direction::Down;
				Move();
				break;
			}
			else if (*c == "Left")
			{
				mDirection = Direction::Left;
				Move();
				break;
			}
			else if (*c == "Right")
			{
				mDirection = Direction::Right;
				Move();
				break;
			}
		}
	}
}