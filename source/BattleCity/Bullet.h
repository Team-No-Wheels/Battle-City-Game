#pragma once
#include "ActionMove.h"
#include "MessageCollision.h"

namespace AnonymousEngine
{
	class ActionShoot;

	class Bullet : public Entity, public EventSubscriber
	{

		RTTI_DECLARATIONS(Bullet, Entity);

	public:

		Bullet();
		Bullet( ActionShoot& parent);
		~Bullet();

		void SetShootParent(ActionShoot& parent);
		ActionMove& MoveComponent();

		void Update(WorldState& worldState) override;
		void Notify(class EventPublisher& publisher);

		bool isStrong;

	private:
		typedef std::pair<Entity*, Entity*> CollisionPair;

		ActionMove* mMoveComponent;
		ActionShoot* mShootParent;
		
	};

	ENTITY_FACTORY_DECLARATIONS(Bullet);
}
