#include "Pch.h"
#include "BasicTankAI.h"
#include "RandomNumbersGenerator.h"
#include "TankPlayer.h"

using namespace std;
using namespace chrono;

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(BasicTankAI);
	ENTITY_FACTORY_DEFINITIONS(BasicTankAI);

	/************************************************************************/
	const float BasicTankAI::DEFAULT_SPEED = 1.0f;
	const int32_t BasicTankAI::DEFAULT_BULLETS_NUM = 1;
	const int32_t BasicTankAI::DEFAULT_ARMOR = 1;
	const uint32_t BasicTankAI::DEFAULT_PROB_TO_SHOOT_IN_MOV = 10;
	const uint32_t BasicTankAI::DEFAULT_PROB_TO_SHOOT_IN_COL_PLAYER = 70;
	const uint32_t BasicTankAI::DEFAULT_PROB_TO_SHOOT_IN_COL_WALL = 50;
	const int32_t BasicTankAI::MAX_PROB = 100;
	const milliseconds BasicTankAI::DEFAULT_SHOT_COOLDOWN_TIME = seconds(1);
	const milliseconds BasicTankAI::MIN_TIME_IN_SAME_DIRECTION = seconds(1);
	const milliseconds BasicTankAI::MAX_TIME_IN_SAME_DIRECTION = seconds(3);

	/************************************************************************/
	BasicTankAI::BasicTankAI(const float speed, const int32_t bulletsNum, const int32_t armor, const uint32_t probToShootInMov) :
		mSpeed(speed), mBulletsNum(bulletsNum), mArmor(armor), mProbToShootWhileMoving(probToShootInMov),
		mCurrentState(State::Idle), mShotCooldownTimer(DEFAULT_SHOT_COOLDOWN_TIME), mMovingInSameDirectionTimer(MAX_TIME_IN_SAME_DIRECTION)
	{
		mMoveComponent->SetSpeed(mSpeed);
		mMoveComponent->SetDirection(ActionMove::Direction::Down);
		mShootComponent->SetCapacityToShoot(mBulletsNum);
	}

	/************************************************************************/
	void BasicTankAI::Update(WorldState& worldState)
	{
		TankBase::Update(worldState);
		worldState.mEntity = this;

		State previousState = mCurrentState;
		switch (previousState)
		{
			case State::Idle:
				DecideNextDestination();
				break;

			case State::Moving:
				HandleMovingState(worldState);
				break;

			case State::Frozen:
				// do nothing
				break;

			default:;
		}

		worldState.mEntity = nullptr;

	}

	/************************************************************************/
	void BasicTankAI::OnCollision(GameObject& otherGameObject)
	{
		// todo depending on the type of collision(tag of the collider of the go passed), we either decrement armor if bullet
		// decide to go idle if it's unbreakable wall, decide to go idle or shoot(50% ~ 70%) if it's brick or flag, or shoot if it's the player
		auto tag = otherGameObject.GetCollider().GetTag();
		switch (tag)
		{
			case Collider::ColliderTag::Player:

				HandleCollisionWithPlayer(otherGameObject);
				break;

			case Collider::ColliderTag::Wall:
			case Collider::ColliderTag::Enemy:

				mCurrentState = State::Idle;
				break;

			case Collider::ColliderTag::PlayerBullet:

				DecrementArmor();
				break;

			case Collider::ColliderTag::EnemyBullet:

				// nothing happens
				break;

			case Collider::ColliderTag::Destructable:
			case Collider::ColliderTag::MuricanEagle:

				HandleCollisionWithDestructable();
				break;

			default:
				// nothing happens
				break;
		}
	}

	/************************************************************************/
	void BasicTankAI::Freeze()
	{
		mCurrentState = State::Frozen;
	}

	/************************************************************************/
	void BasicTankAI::Unfreeze()
	{
		mCurrentState = State::Idle;
	}

	/************************************************************************/
	bool BasicTankAI::DecrementArmor()
	{
		if (mArmor > 0)
		{
			--mArmor;
		}

		if (mArmor == 0)
		{
			// todo mark this for delete
			return true;
		}
		return false;
	}

	/************************************************************************/
	void BasicTankAI::HandleMovingState(const WorldState& worldState)
	{
		// check if the ai has been moving in the same direction in a while
		if (mMovingInSameDirectionTimer > milliseconds::zero())
		{
			mMovingInSameDirectionTimer -= worldState.mGameTime.ElapsedGameTime();
		}
		else
		{
			auto millisecs = RandomNumbersGenerator::GetInstance().GetRangedRandom(static_cast<int32_t>(MAX_TIME_IN_SAME_DIRECTION.count()), static_cast<int32_t>(MIN_TIME_IN_SAME_DIRECTION.count()));
			mMovingInSameDirectionTimer = milliseconds(millisecs);
			mCurrentState = State::Idle;
			return;
		}

		// check if the ai can shoot
		if (mShotCooldownTimer > milliseconds::zero())
		{
			mShotCooldownTimer -= worldState.mGameTime.ElapsedGameTime();
		}
		else
		{
			TryToShoot(mProbToShootWhileMoving);
			mShotCooldownTimer = DEFAULT_SHOT_COOLDOWN_TIME;
		}
	}

	/************************************************************************/
	void BasicTankAI::DecideNextDestination()
	{
		// randomly select a direction
		auto prob = RandomNumbersGenerator::GetInstance().GetRangedRandom(3);
		ActionMove::Direction dir;
		switch (prob)
		{
			case 0: dir = ActionMove::Direction::Up; break;
			case 1: dir = ActionMove::Direction::Right; break;
			case 2: dir = ActionMove::Direction::Down; break;
			case 3: dir = ActionMove::Direction::Left; break;
			default: dir = ActionMove::Direction::Down; break;
		}
		mMoveComponent->SetDirection(dir);
		mCurrentState = State::Moving;
	}

	/************************************************************************/
	void BasicTankAI::HandleCollisionWithPlayer(const GameObject& gameObject)
	{
		auto playerGo = gameObject.As<TankPlayer>();
		if (playerGo)
		{
			// face the player
			auto playerDir = playerGo->MoveComponent().GetDirection();
			ActionMove::Direction aiDir;
			switch (playerDir)
			{
				case ActionMove::Direction::Up:
					aiDir = ActionMove::Direction::Down;
					break;

				case ActionMove::Direction::Down:
					aiDir = ActionMove::Direction::Up;
					break;

				case ActionMove::Direction::Left:
					aiDir = ActionMove::Direction::Right;
					break;

				case ActionMove::Direction::Right:
					aiDir = ActionMove::Direction::Left;
					break;

				default:
					aiDir = ActionMove::Direction::Down;
					break;
			}
			mMoveComponent->SetDirection(aiDir);

			// try to shoot the player
			TryToShoot(DEFAULT_PROB_TO_SHOOT_IN_COL_PLAYER);
		}
	}

	/************************************************************************/
	void BasicTankAI::HandleCollisionWithDestructable()
	{
		TryToShoot(DEFAULT_PROB_TO_SHOOT_IN_COL_WALL);
		mCurrentState = State::Idle;
	}

	/************************************************************************/
	void BasicTankAI::TryToShoot(const uint32_t probability) const
	{
		auto prob = RandomNumbersGenerator::GetInstance().GetRangedRandom(MAX_PROB);
		if (prob <= static_cast<int32_t>(probability) && mShootComponent->CanShoot())
		{
			mShootComponent->CreateBullet();
		}
	}

	/************************************************************************/
	void BasicTankAI::AppendPrescribedAttributeNames(Vector<string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}
}
