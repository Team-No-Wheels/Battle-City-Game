#include "Pch.h"
#include "Bullet.h"
#include "TankPlayer.h"
#include "ScoreMessageStructs.h"
#include "World.h"

namespace AnonymousEngine
{
	using namespace BattleCity::MapEntities;

	ATTRIBUTED_DEFINITIONS(Bullet);

	/************************************************************************/
	Bullet::Bullet(ActionShoot* parent) :
		mMoveComponent(CreateAction("MovementComponent", "ActionMove").As<ActionMove>()),
		mShootParent(parent)
	{
	}

	/************************************************************************/
	void Bullet::SetShootParent(ActionShoot& parent)
	{
		mShootParent = &parent;
	}

	/************************************************************************/
	ActionShoot* Bullet::GetShootParent()
	{
		return mShootParent;
	}

	/************************************************************************/
	ActionMove& Bullet::GetMoveComponent()
	{
		return *mMoveComponent;
	}

	/************************************************************************/
	void Bullet::Update(WorldState& worldState)
	{
		GameObject::Update(worldState);

		worldState.mEntity = this;

		worldState.mEntity = nullptr;
	}

	/************************************************************************/
	void Bullet::OnCollision(GameObject& otherGameObject)
	{
		auto tag = otherGameObject.GetCollider().GetTag();

		switch (tag)
		{
			case Collider::ColliderTag::Player:
				CollisionWithPlayer(*otherGameObject.As<TankPlayer>());
				break;

			case Collider::ColliderTag::Enemy:
				CollisionWithEnemy(*otherGameObject.As<BasicTankAI>());
				break;

			case Collider::ColliderTag::PlayerBullet:
			{
				auto bullet = otherGameObject.As<Bullet>();
				if (!bullet->GetShootParent()->IsOwnedByPlayer())
				{
					CollisionWithOtherBullet(*bullet);
				}
				break;
			}

			case Collider::ColliderTag::EnemyBullet:
			{
				auto otherBullet = otherGameObject.As<Bullet>();
				if (otherBullet->GetShootParent()->IsOwnedByPlayer())
				{
					CollisionWithOtherBullet(*otherBullet);
				}
				break;
			}

			case Collider::ColliderTag::MetalWall:
				CollisionWithMetalWall(*otherGameObject.As<Metal>());
				break;

			case Collider::ColliderTag::BrickWall:
				CollisionWithBrickWall(*otherGameObject.As<Brick>());
				break;

			case Collider::ColliderTag::MuricanEagle:
				CollisionWithFlag();
				break;

			case Collider::ColliderTag::MapBorder:
				mShootParent->KillBullet(*this);
				break;

			default:
				// do nothing
				break;
		}
	}

	/************************************************************************/
	void Bullet::CollisionWithPlayer(TankPlayer& player)
	{
		if (!player.IsInvincible())
		{
			player.Respawn();
		}
		mShootParent->KillBullet(*this);
	}

	/************************************************************************/
	void Bullet::CollisionWithEnemy(BasicTankAI& ai)
	{
		if (mShootParent->IsOwnedByPlayer())
		{
			bool isDead = ai.DecrementArmor();
			if (isDead)
			{
				WorldState* state = GetWorldState();
				std::string tankType = ai.GetTankType();
				ScoreEventMessage scoreMessage(tankType, *state);
				const std::shared_ptr<Core::Event<ScoreEventMessage>> eventptr = std::make_shared<Core::Event<ScoreEventMessage>>(scoreMessage);
				state->mWorld->EventQueue().Enqueue(eventptr, state->mGameTime, 0u);
			}

			mShootParent->KillBullet(*this);
		}
	}

	/************************************************************************/
	void Bullet::CollisionWithOtherBullet(Bullet& bullet)
	{
		bullet;
		mShootParent->KillBullet(*this);
	}

	/************************************************************************/
	void Bullet::CollisionWithMetalWall(Metal& metal)
	{
		if (mShootParent->IsStrong())
		{
			metal.SetMarkForDelete();
		}
		mShootParent->KillBullet(*this);
	}

	/************************************************************************/
	void Bullet::CollisionWithBrickWall(Brick& brick)
	{
		brick.SetMarkForDelete();
		mShootParent->KillBullet(*this);
	}

	/************************************************************************/
	void Bullet::CollisionWithFlag()
	{
		WorldState* state = GetWorldState();

		PlayerSideDamageMessage damageMessage(true, *state);
		const std::shared_ptr<Core::Event<PlayerSideDamageMessage>> eventptr = std::make_shared<Core::Event<PlayerSideDamageMessage>>(damageMessage);
		state->mWorld->EventQueue().Enqueue(eventptr, state->mGameTime, 0u);

		mShootParent->KillBullet(*this);
	}

	/************************************************************************/
	void Bullet::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	ENTITY_FACTORY_DEFINITIONS(Bullet);
}
