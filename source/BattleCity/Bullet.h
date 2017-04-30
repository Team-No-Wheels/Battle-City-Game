#pragma once
#include "ActionMove.h"
#include "MessageCollision.h"
#include "GameObject.h"
#include "BasicTankAI.h"
#include "Brick.h"
#include "Metal.h"
#include "ScoreMessageStructs.h"

namespace AnonymousEngine
{
	using namespace BattleCity::MapEntities;

	class ActionShoot;

	class Bullet : public GameObject
	{

		ATTRIBUTED_DECLARATIONS(Bullet, GameObject);

	public:

		Bullet();
		Bullet( ActionShoot& parent);
		~Bullet();

		void SetShootParent(ActionShoot& parent);
		ActionMove& MoveComponent();

		void Update(WorldState& worldState) override;

		void OnCollision(GameObject& otherGameObject) override;

		bool isStrong;

	private:
		typedef std::pair<Entity*, Entity*> CollisionPair;

		ActionMove* mMoveComponent;
		ActionShoot* mShootParent;
		bool isPendingKill;

		void CollisionWithPlayer(TankPlayer& player);
		void CollisionWithEnemy(BasicTankAI& ai);
		void CollisionWithBrick(Brick& brick);
		void CollisionWithMetal(Metal& metal);
		WorldState* FindWorldState();
		
	};

	ENTITY_FACTORY_DECLARATIONS(Bullet);
}
