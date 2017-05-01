#include "Pch.h"
#include "ActionMove.h"
#include "TankPlayer.h"

namespace AnonymousEngine
{
	const float ActionMove::sDefaultSpeed = 1;

	ATTRIBUTED_DEFINITIONS(ActionMove);

	ActionMove::ActionMove() :
		mDirection(Direction::Up), mSpeed(sDefaultSpeed), mIsPlayer(false), mCanMove(true)
	{
		if (GetParent()->Is(TankPlayer::TypeIdClass()))
		{
			mIsPlayer = true;
		}
	}

	void ActionMove::Update(WorldState& worldState)
	{
		worldState.mAction = this;

		// In case enemy unit.
		if (!mIsPlayer && mCanMove)
		{
			Move(worldState);
		}
		
		worldState.mAction = nullptr;
	}

	void ActionMove::Move(WorldState& worldState)
	{
		// Get a reference to parent as a game object.
		GameObject* gameObject = GetParent()->As<GameObject>();
		 std::int64_t deltaTime = worldState.mGameTime.ElapsedGameTime().count();

		if (gameObject != nullptr)
		{
			glm::vec4 position = gameObject->GetPosition();

			// Update position.
			switch (mDirection)
			{
				case Direction::Up:
					position.y += (mSpeed * deltaTime) / 1000;
					break;
				case Direction::Down:
					position.y -= (mSpeed * deltaTime) / 1000;
					break;
				case Direction::Left:
					position.x -= (mSpeed * deltaTime) / 1000;
					break;
				case Direction::Right:
					position.x += (mSpeed * deltaTime) / 1000;
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

	void ActionMove::SetDirection(const Direction direction)
	{
		mDirection = direction;
	}

	ActionMove::Direction ActionMove::GetDirection() const
	{
		return mDirection;
	}

	bool ActionMove::GetCanMove() const
	{
		return mCanMove;
	}

	void ActionMove::SetCanMove(bool canMove /* = true */)
	{
		mCanMove = canMove;
	}

	void ActionMove::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}
}
