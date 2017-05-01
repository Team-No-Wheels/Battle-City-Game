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

	class Bullet final : public GameObject
	{

		ATTRIBUTED_DECLARATIONS(Bullet, GameObject);

	public:

		Bullet(ActionShoot* parent = nullptr);
		~Bullet() = default;

		void SetShootParent(ActionShoot& parent);

		/** Return the shoot parent.
			@return A reference to the shoot parent.
		*/
		ActionShoot* GetShootParent();
		ActionMove& GetMoveComponent();

		void Update(WorldState& worldState) override;

		void OnCollision(GameObject& otherGameObject) override;

	private:

		ActionMove* mMoveComponent;
		ActionShoot* mShootParent;

		void CollisionWithPlayer(TankPlayer& player);
		void CollisionWithEnemy(BasicTankAI& ai);
		void CollisionWithOtherBullet(Bullet& bullet);
		void CollisionWithMetalWall(Metal& metal);
		void CollisionWithBrickWall(Brick& brick);
		void CollisionWithFlag();
		WorldState* FindWorldState() const;
		
	};

	ENTITY_FACTORY_DECLARATIONS(Bullet);
}
