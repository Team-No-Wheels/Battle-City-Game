#pragma once
#include "ActionMove.h"
#include "MessageCollision.h"
#include "GameObject.h"
#include "BasicTankAI.h"
#include "Brick.h"
#include "Metal.h"
#include "Flag.h"
#include "ScoreMessageStructs.h"

namespace AnonymousEngine
{
	using namespace BattleCity::MapEntities;

	class ActionShoot;

	class Bullet : public GameObject
	{

		ATTRIBUTED_DECLARATIONS(Bullet, GameObject);

	public:

		Bullet(ActionShoot* parent = nullptr);
		~Bullet();

		void SetShootParent(ActionShoot& parent);

		/** Return the shoot parent.
			@return A reference to the shoot parent.
		*/
		ActionShoot* GetShootParent();
		ActionMove& MoveComponent();

		void Update(WorldState& worldState) override;

		void OnCollision(GameObject& otherGameObject) override;

	private:
		typedef std::pair<Entity*, Entity*> CollisionPair;

		ActionMove* mMoveComponent;
		ActionShoot* mShootParent;
		bool mIsPendingKill;

		void CollisionWithPlayer(TankPlayer& player);
		void CollisionWithEnemy(BasicTankAI& ai);
		void CollisionWithBrick(Brick& brick);
		void CollisionWithMetal(Metal& metal);
		void CollisionWithFlag(Flag& flag);
		WorldState* FindWorldState();
		
	};

	ENTITY_FACTORY_DECLARATIONS(Bullet);
}
