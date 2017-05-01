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

		virtual void Update(WorldState& worldState) override;
		ActionMove& MoveComponent();

	protected:

		ActionShoot* mShootComponent;
		ActionMove* mMoveComponent;

	//private:
	//	static const std::string sShootComponentName;
	//	static const std::string sMoveComponentName;
	};
}
