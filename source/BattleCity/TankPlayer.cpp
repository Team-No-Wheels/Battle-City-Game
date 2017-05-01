#include "Pch.h"
#include "TankPlayer.h"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(TankPlayer);

	TankPlayer::TankPlayer() :
		mIsInvincible(false), mStars(0), mTimeInvincible(0)
	{
		Event<MessageInput>::Subscribe(*this);
	}

	TankPlayer::~TankPlayer()
	{
		Event<MessageInput>::Unsubscribe(*this);
	}

	void TankPlayer::IncrementStars()
	{
		if (mStars < 3)
		{
			++mStars;
			if (mStars == 2)
				mShootComponent->SetCapacityToShoot(2);
		}
	}

	void TankPlayer::SetInvincibility(bool state)
	{
		mIsInvincible = state;
	}

	bool TankPlayer::IsInvincible() const
	{
		return mIsInvincible;
	}

	void TankPlayer::Update(WorldState& worldState)
	{
		Entity::Update(worldState);

		worldState.mEntity = this;

		if (mIsInvincible)
		{
			SetInvincibility((mTimeInvincible += worldState.mGameTime.ElapsedGameTime()) < mInvincbleLimit);
		}

		worldState.mEntity = nullptr;
	}

	void TankPlayer::Notify(class EventPublisher& publisher)
	{
		Event<MessageInput>* curEvent = publisher.As<Event<MessageInput>>();

		if (curEvent != nullptr)
		{
			MessageInput* message = &const_cast<MessageInput&>(curEvent->Message());
			Vector<std::string>& Keys = message->GetKeys();
			WorldState& worldState = message->GetWorldState();

			// React To Certain Key Presses
			for (const auto& key : Keys)
			{
				// Move Up
				if (key == "Up")
				{
					mMoveComponent->SetDirection(ActionMove::Direction::Up);
					mMoveComponent->Move(worldState);
					break;
				}

				// Move Down
				else if (key == "Down")
				{
					mMoveComponent->SetDirection(ActionMove::Direction::Down);
					mMoveComponent->Move(worldState);
					break;
				}

				// Move Left
				else if (key == "Left")
				{
					mMoveComponent->SetDirection(ActionMove::Direction::Left);
					mMoveComponent->Move(worldState);
					break;
				}

				// Move Right
				else if (key == "Right")
				{
					mMoveComponent->SetDirection(ActionMove::Direction::Right);
					mMoveComponent->Move(worldState);
					break;
				}

				// Try Shooting
				if (key == "Shoot" && mShootComponent->CanShoot())
				{
					mShootComponent->CreateBullet();
					break;
				}
			}
		}
	}

	void TankPlayer::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	ENTITY_FACTORY_DEFINITIONS(TankPlayer);
}
