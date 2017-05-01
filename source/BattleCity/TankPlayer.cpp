#include "Pch.h"
#include "TankPlayer.h"
#include "ScoreMessageStructs.h"
#include "World.h"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(TankPlayer);

	const std::chrono::milliseconds TankPlayer::sInvincbleLimitOnRespawn = std::chrono::seconds(2);
	const std::chrono::milliseconds TankPlayer::sInvincbleLimitOnPoweUp = std::chrono::seconds(5);

	/************************************************************************/
	TankPlayer::TankPlayer() :
		mStars(0), mTimeInvincible(0), mIsInvincible(false)
	{
		Event<MessageInput>::Subscribe(*this);
	}

	/************************************************************************/
	TankPlayer::~TankPlayer()
	{
		Event<MessageInput>::Unsubscribe(*this);
	}

	/************************************************************************/
	void TankPlayer::IncrementStars()
	{
		if (mStars < 3)
		{
			++mStars;
			switch (mStars)
			{
				case 1:
					mShootComponent->SetIsFast(true);
					break;
				case 2:
					mShootComponent->SetCapacityToShoot(2);
					break;
				case 3:
					mShootComponent->SetIsStrong(true);
					break;
				default:
					break;
			}

		}
	}

	/************************************************************************/
	void TankPlayer::SetInvincibility(bool onRespawn)
	{
		mIsInvincible = true;
		if (onRespawn)
		{
			mTimeInvincible = sInvincbleLimitOnRespawn;
		}
		else
		{
			mTimeInvincible = sInvincbleLimitOnPoweUp;
		}
	}

	/************************************************************************/
	bool TankPlayer::IsInvincible() const
	{
		return mIsInvincible;
	}

	/************************************************************************/
	void TankPlayer::Update(WorldState& worldState)
	{
		TankBase::Update(worldState);

		worldState.mEntity = this;

		if (mIsInvincible && mTimeInvincible > std::chrono::milliseconds::zero())
		{
			mTimeInvincible -= worldState.mGameTime.ElapsedGameTime();
		}
		else
		{
			mIsInvincible = false;
		}

		worldState.mEntity = nullptr;
	}

	/************************************************************************/
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
					//mMoveComponent->Move(worldState);
					break;
				}

				// Move Down
				else if (key == "Down")
				{
					mMoveComponent->SetDirection(ActionMove::Direction::Down);
					//mMoveComponent->Move(worldState);
					break;
				}

				// Move Left
				else if (key == "Left")
				{
					mMoveComponent->SetDirection(ActionMove::Direction::Left);
					//mMoveComponent->Move(worldState);
					break;
				}

				// Move Right
				else if (key == "Right")
				{
					mMoveComponent->SetDirection(ActionMove::Direction::Right);
					//mMoveComponent->Move(worldState);
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

	/************************************************************************/
	void TankPlayer::OnCollision(GameObject& otherGameObject)
	{
		auto tag = otherGameObject.GetCollider().GetTag();

		switch (tag)
		{
			case Collider::ColliderTag::Enemy:
			case Collider::ColliderTag::MetalWall:
			case Collider::ColliderTag::BrickWall:
			case Collider::ColliderTag::MapBorder:
			case Collider::ColliderTag::Water:
			case Collider::ColliderTag::MuricanEagle:
				mMoveComponent->SetCanMove(false);
				break;

			default:

				break;
		}
	}

	/************************************************************************/
	void TankPlayer::Respawn()
	{
		WorldState* state = GetWorldState();

		PlayerSideDamageMessage damageMessage(false, *state);
		const std::shared_ptr<Core::Event<PlayerSideDamageMessage>> eventptr = std::make_shared<Core::Event<PlayerSideDamageMessage>>(damageMessage);
		state->mWorld->EventQueue().Enqueue(eventptr, state->mGameTime, 0u);

		// todo set position
		SetInvincibility(true);
	}

	/************************************************************************/
	void TankPlayer::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	ENTITY_FACTORY_DEFINITIONS(TankPlayer);
}
