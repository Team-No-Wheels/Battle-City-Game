#pragma once
#include "ActionShoot.h"
#include "ActionMove.h"

namespace AnonymousEngine
{

	class TankBase : public Entity
	{

		RTTI_DECLARATIONS(TankBase, Entity);

	public:

		TankBase();
		virtual ~TankBase();

		ActionMove& MoveComponent();

	protected:

		ActionMove* mMoveComponent;
		ActionShoot* mShootComponent;

	};
}
