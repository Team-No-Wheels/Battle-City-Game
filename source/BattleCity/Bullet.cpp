#include "Pch.h"
#include "Bullet.h"
#include "TankPlayer.h"
#include "ScoreMessageStructs.h"
#include "World.h"

namespace AnonymousEngine
{
	using namespace BattleCity::MapEntities;
	ATTRIBUTED_DEFINITIONS(Bullet);

	Bullet::Bullet() :
		mMoveComponent(CreateAction("MovementComponent", "ActionMove").As<ActionMove>()),
		mShootParent(nullptr), isStrong(false), isPendingKill(false)
	{
	}

	Bullet::Bullet(ActionShoot& parent) :
		mMoveComponent(CreateAction("MovementComponent", "ActionMove").As<ActionMove>()),
		mShootParent(&parent)
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
		if(!isPendingKill)
		{
			mShootParent->PendKillBullet(*this);
			isPendingKill = true;

			// Check If Player
			TankPlayer* player = otherGameObject.As<TankPlayer>();
			if (player != nullptr)
			{
				CollisionWithPlayer(*player);
				return;
			}

			// Check If Enemy Tank
			BasicTankAI* AI = otherGameObject.As<BasicTankAI>();
			if (AI != nullptr)
			{
				CollisionWithEnemy(*AI);
				return;
			}

			// Check If Walls
			Brick* brick = otherGameObject.As<Brick>();
			if (brick != nullptr)
			{
				CollisionWithBrick(*brick);
				return;
			}

			Metal* metal = otherGameObject.As<Metal>();
			if (metal != nullptr)
			{
				CollisionWithMetal(*metal);
				return;
			}

			// Check If Flag
			Flag* flag = otherGameObject.As<Flag>();
			if (flag != nullptr)
			{
				CollisionWithFlag(*flag);
				return;
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
		UNREFERENCED_PARAMETER(ai);
//		WorldState* state = FindWorldState();
// 		std::string tankType = //GET TANK TYPE NAME STRING
// 		ScoreEventMessage scoreMessage(tankType, state);
// 		const std::shared_ptr<Core::Event<PlayerscoreMessageSideDamageMessage>> eventptr = std::make_shared<Core::Event<scoreMessage>>(scoreMessage);
// 		state->mWorld->EventQueue().Enqueue(eventptr, state->mGameTime, 0u);
		
	}

	void Bullet::CollisionWithBrick(Brick& brick)
	{
		UNREFERENCED_PARAMETER(brick);
	}

	void Bullet::CollisionWithMetal(Metal& metal)
	{
		UNREFERENCED_PARAMETER(metal);
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
