#include "Pch.h"
#include "ActionMove.h"
#include "TankPlayer.h"

using namespace AnonymousEngine;
RTTI_DEFINITIONS(ActionMove);

//TODO
// Find Way To Track Position
// Update Position

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
	Event<MessageInput>::Unsubscribe(*this);
}

void ActionMove::Update(WorldState& worldState)
{
	UNREFERENCED_PARAMETER(worldState);
	if(mIsEnemy)
		Move();
}

void ActionMove::Move()
{
	switch (mDirection)
	{
	case Direction::Up :
		break;

	case Direction::Down:
		break;

	case Direction::Left:
		break;

	case Direction::Right:
		break;

	default:
		break;
	}
}

void ActionMove::SetDirection(Direction direction)
{
	mDirection = direction;
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