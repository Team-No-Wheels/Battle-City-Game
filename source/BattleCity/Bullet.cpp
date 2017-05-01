#include "Pch.h"
#include "Bullet.h"
#include "TankPlayer.h"
#include "ScoreMessageStructs.h"
#include "World.h"

namespace AnonymousEngine
{
	using namespace BattleCity::MapEntities;
	ATTRIBUTED_DEFINITIONS(Bullet);

	Bullet::Bullet(ActionShoot* parent) :
		mMoveComponent(CreateAction("MovementComponent", "ActionMove").As<ActionMove>()),
		mShootParent(parent)
	{
	}

	Bullet::~Bullet()
	{
		mShootParent = nullptr;
	}

	void Bullet::SetShootParent(ActionShoot& parent)
	{
		mShootParent = &parent;
	}

	ActionShoot* Bullet::GetShootParent()
	{
		return mShootParent;
	}

	ActionMove& Bullet::MoveComponent()
	{
		return *mMoveComponent;
	}

	void Bullet::Update(WorldState& worldState)
	{
		Entity::Update(worldState);

		worldState.mEntity = this;

		worldState.mEntity = nullptr;
	}

	void Bullet::OnCollision(GameObject& otherGameObject)
	{
		if(!mIsPendingKill)
		{

			bool shouldKillBullet = false;;

			// Check If Player
			TankPlayer* player = otherGameObject.As<TankPlayer>();
			if (player != nullptr)
			{
				shouldKillBullet = true;
				CollisionWithPlayer(*player);
				return;
			}

			// Check If Enemy Tank
			BasicTankAI* AI = otherGameObject.As<BasicTankAI>();
			if (AI != nullptr)
			{
				shouldKillBullet = true;
				CollisionWithEnemy(*AI);
				return;
			}

			// Check If Walls
			Brick* brick = otherGameObject.As<Brick>();
			if (brick != nullptr)
			{
				shouldKillBullet = true;
				CollisionWithBrick(*brick);
				return;
			}

			Metal* metal = otherGameObject.As<Metal>();
			if (metal != nullptr)
			{
				shouldKillBullet = true;
				CollisionWithMetal(*metal);
				return;
			}

			// Check If Flag
			Flag* flag = otherGameObject.As<Flag>();
			if (flag != nullptr)
			{
				shouldKillBullet = true;
				CollisionWithFlag(*flag);
				return;
			}

			// If this is the player bullet check if the collision
			// is with the enemy bullet
			if (mShootParent->IsPlayer())
			{
				Bullet* bullet = otherGameObject.As<Bullet>();
				if (!(bullet->GetShootParent()->IsPlayer()))
				{
					shouldKillBullet = true;
					bullet->SetMarkForDelete();
				}
			}

			if (shouldKillBullet)
			{
				mShootParent->KillBullet(*this);
				mIsPendingKill = true;
			}
		}
	}

	void Bullet::CollisionWithPlayer(TankPlayer& player)
	{
		if (!player.IsInvincible())
		{
			WorldState* state = FindWorldState();

			PlayerSideDamageMessage damageMessage(false, *state);
			const std::shared_ptr<Core::Event<PlayerSideDamageMessage>> eventptr = std::make_shared<Core::Event<PlayerSideDamageMessage>>(damageMessage);
			state->mWorld->EventQueue().Enqueue(eventptr, state->mGameTime, 0u);
		}
	}

	void Bullet::CollisionWithEnemy(BasicTankAI& ai)
	{
		bool isDead = ai.DecrementArmor();
		if (isDead)
		{
			WorldState* state = FindWorldState();
			std::string tankType = ai.GetTankType();
			ScoreEventMessage scoreMessage(tankType, *state);
			const std::shared_ptr<Core::Event<ScoreEventMessage>> eventptr = std::make_shared<Core::Event<ScoreEventMessage>>(scoreMessage);
			state->mWorld->EventQueue().Enqueue(eventptr, state->mGameTime, 0u);
		}
	}

	void Bullet::CollisionWithBrick(Brick& brick)
	{
		brick.SetMarkForDelete();
	}

	void Bullet::CollisionWithMetal(Metal& metal)
	{
		if (mShootParent->IsStrong())
		{
			metal.SetMarkForDelete();
		}
	}

	void Bullet::CollisionWithFlag(Flag& flag)
	{
		UNREFERENCED_PARAMETER(flag);

		WorldState* state = FindWorldState();

		PlayerSideDamageMessage damageMessage(true, *state);
		const std::shared_ptr<Core::Event<PlayerSideDamageMessage>> eventptr = std::make_shared<Core::Event<PlayerSideDamageMessage>>(damageMessage);
		state->mWorld->EventQueue().Enqueue(eventptr, state->mGameTime, 0u);
	}

	WorldState* Bullet::FindWorldState()
	{
		WorldState* state = nullptr;
		Scope* curScope = mShootParent->GetParent();

		// Loop Through Parent To Find World
		while (curScope->GetParent() != nullptr)
		{
			curScope = curScope->GetParent();

			// If World, Return WorldState
			if (curScope->Is(World::TypeIdClass()))
			{
				state = &curScope->As<World>()->GetWorldState();
			}
		}

		return state;
	}

	void Bullet::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	ENTITY_FACTORY_DEFINITIONS(Bullet);
}
