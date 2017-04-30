#pragma once
#include "ActionShoot.h"
#include "ActionMove.h"
#include "GameObject.h"

namespace AnonymousEngine
{

	class TankBase : public Core::GameObject
	{

		ATTRIBUTED_DECLARATIONS(TankBase, Core::GameObject);

	public:

		TankBase();
		virtual ~TankBase();

		ActionMove& MoveComponent();

	protected:

		ActionMove* mMoveComponent;
		ActionShoot* mShootComponent;

	};
}
