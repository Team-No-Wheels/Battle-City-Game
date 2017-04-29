#include "Pch.h"
#include "ActionMove.h"
#include "TankPlayer.h"

using namespace AnonymousEngine;
RTTI_DEFINITIONS(ActionMove);

ActionMove::ActionMove() :
	mDirection(Direction::Up), mSpeed(1), mIsEnemy(true)
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
	UNREFERENCED_PARAMETER(worldState);
	if(mIsEnemy)
		Move();
}

void ActionMove::Move()
{
	Entity* entity = GetParent()->As<Entity>();

	if(entity != nullptr)
	{
		glm::vec2* position = &entity->GetPosition();

		switch (mDirection)
		{
		case Direction::Up:
			position->y + 1;
			break;

		case Direction::Down:
			position->y - 1;
			break;

		case Direction::Left:
			position->x - 1;
			break;

		case Direction::Right:
			position->x + 1;
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

void ActionMove::Notify(class EventPublisher& publisher)
{
	Event<MessageInput>* curEvent = publisher.As<Event<MessageInput>>();

	if (curEvent != nullptr)
	{
		MessageInput* message = &const_cast<MessageInput&>(curEvent->Message());
		Vector<std::string*>* Keys = &message->GetKeys();

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