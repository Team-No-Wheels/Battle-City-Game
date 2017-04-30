#include "Pch.h"
#include "ActionMove.h"
#include "TankPlayer.h"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(ActionMove);

	ActionMove::ActionMove() :
		mDirection(Direction::Up), mSpeed(1), mIsEnemy(true), mCanMove(true)
	{
		if (GetParent()->Is(TankPlayer::TypeIdClass()))
		{
			mIsEnemy = false;
		}
	}

	void ActionMove::Update(WorldState& worldState)
	{
		worldState.mAction = this;

		// Automatically Move If Enemy. Enemy AI will change Speed/Direction
		if (mIsEnemy)
			Move();

		worldState.mAction = nullptr;
	}

	void ActionMove::Move()
	{
		// Get A Reference To Parent As Entity
		GameObject* gameObject = GetParent()->As<GameObject>();

		if (gameObject != nullptr)
		{
			glm::vec4 position = gameObject->GetPosition();

			// Update Position Based On Direction
			switch (mDirection)
			{
				case Direction::Up:
					position.y += mSpeed;
					break;
				case Direction::Down:
					position.y -= mSpeed;
					break;
				case Direction::Left:
					position.x -= mSpeed;
					break;
				case Direction::Right:
					position.x += mSpeed;
					break;
				default:
					break;
			}
			gameObject->SetPosition(position);
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

	ActionMove::Direction ActionMove::GetDirection() const
	{
		return mDirection;
	}

	void ActionMove::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

}
