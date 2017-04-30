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
		Event<MessageCollision>::Subscribe(*this);
	}

	Bullet::Bullet(ActionShoot& parent) :
		mMoveComponent(CreateAction("MovementComponent", "ActionMove").As<ActionMove>()),
		mShootParent(&parent)
	{
		Event<MessageCollision>::Subscribe(*this);
	}

	Bullet::~Bullet()
	{
		Event<MessageCollision>::Unsubscribe(*this);
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

			// Do Stuff if Flag
			/*
			PlayerSideDamageMessage damageMessage(true, message->WorldState());
			const std::shared_ptr<Core::Event<PlayerSideDamageMessage>> eventptr = std::make_shared<Core::Event<PlayerSideDamageMessage>>(damageMessage);
			message->WorldState().mWorld->EventQueue().Enqueue(eventptr, message->WorldState().mGameTime, 0u);
			*/
		}
	}

	void Bullet::CollisionWithPlayer(TankPlayer& player)
	{
		WorldState* state = FindWorldState();

		if (!player.IsInvincible())
		{
			PlayerSideDamageMessage damageMessage(false, *state);
			const std::shared_ptr<Core::Event<PlayerSideDamageMessage>> eventptr = std::make_shared<Core::Event<PlayerSideDamageMessage>>(damageMessage);
			state->mWorld->EventQueue().Enqueue(eventptr, state->mGameTime, 0u);
		}
		else
		{
			// Damage Player
		}
	}

	void Bullet::CollisionWithEnemy(BasicTankAI& ai)
	{
		WorldState* state = FindWorldState();
// 		std::string tankType = //GET TANK TYPE NAME STRING
// 		ScoreEventMessage scoreMessage(tankType, state);
// 		const std::shared_ptr<Core::Event<PlayerscoreMessageSideDamageMessage>> eventptr = std::make_shared<Core::Event<scoreMessage>>(scoreMessage);
// 		state->mWorld->EventQueue().Enqueue(eventptr, state->mGameTime, 0u);
		
	}

	void Bullet::CollisionWithBrick(Brick& brick)
	{

	}

	void Bullet::CollisionWithMetal(Metal& metal)
	{

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
