#include "Pch.h"
#include "TankPlayer.h"

using namespace AnonymousEngine;
RTTI_DEFINITIONS(TankPlayer);

TankPlayer::TankPlayer() :
	mLives(2), mMaxLives(9), mIsInvincible(false), mStars(0), mTimeInvincible(0)
{
	Event<MessageInput>::Subscribe(*this);
}

TankPlayer::~TankPlayer()
{
	Event<MessageInput>::Unsubscribe(*this);
}

void TankPlayer::IncrementLives()
{
	if (mLives < mMaxLives)
	{
		++mLives;
	}
}

void TankPlayer::DecrementLives()
{
	if (mLives == 0)
	{
		// Game Over
	}

	else
	{
		--mLives;
	}
}

void TankPlayer::IncrementStars()
{
	if (mStars < 3)
		++mStars;
}

void TankPlayer::SetInvincibility(bool state)
{
	mIsInvincible = state;
}

bool TankPlayer::IsInvincible()
{
	return mIsInvincible;
}

void TankPlayer::Update(WorldState& worldState)
{
	Entity::Update(worldState);

	worldState.mEntity = this;

	if (mIsInvincible)
	{
		SetInvincibility( (mTimeInvincible += worldState.mGameTime.ElapsedGameTime()) < mInvincbleLimit);
	}

	worldState.mEntity = nullptr;
}

void TankPlayer::Notify(class EventPublisher& publisher)
{
	Event<MessageInput>* curEvent = publisher.As<Event<MessageInput>>();

	if (curEvent != nullptr)
	{
		MessageInput* message = &const_cast<MessageInput&>(curEvent->Message());
		Vector<std::string*>* Keys = &message->GetKeys();

		// React To Certain Key Presses
		for (std::string* c : *Keys)
		{
			// Move Up
			if (*c == "Up")
			{
				mMoveComponent->SetDirection(ActionMove::Direction::Up);
				mMoveComponent->Move();
				break;
			}
			
			// Move Down
			else if (*c == "Down")
			{
				mMoveComponent->SetDirection(ActionMove::Direction::Down);
				mMoveComponent->Move();
				break;
			}
			
			// Move Left
			else if (*c == "Left")
			{
				mMoveComponent->SetDirection(ActionMove::Direction::Left);
				mMoveComponent->Move();
				break;
			}
			
			// Move Right
			else if (*c == "Right")
			{
				mMoveComponent->SetDirection(ActionMove::Direction::Right);
				mMoveComponent->Move();
				break;
			}

			// Try Shooting
			if (*c == "Shoot" && mShootComponent->CanShoot())
			{
				mShootComponent->CreateBullet();

				// Delay Creation Of 2nd Bullet For Double Shot
				if (mShootComponent->IsDouble())
				{
					std::async(std::launch::async, [this]()
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(10));
						mShootComponent->CreateBullet();
					});
				}

				break;
			}
		}
	}
}