#include "Pch.h"
#include "TankBase.h"

#define MOVE_COMP_NAME "MoveComponent"
#define SHOOT_COMP_NAME "ShootComponent"
#define ACTION_SHOOT_NAME "ActionShoot"
#define ACTION_MOVE_NAME "ActionMove"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(TankBase);

	//const std::string TankBase::sMoveComponentName = "MoveComponent";
	//const std::string TankBase::sShootComponentName = "ShootComponent";

	TankBase::TankBase() :
		mShootComponent(CreateAction(SHOOT_COMP_NAME, ACTION_SHOOT_NAME).As<ActionShoot>()),
		mMoveComponent(CreateAction(MOVE_COMP_NAME, ACTION_MOVE_NAME).As<ActionMove>())
	{
	}

	TankBase::~TankBase()
	{

	}

	ActionMove& TankBase::MoveComponent()
	{
		if (!mMoveComponent)
		{
			std::runtime_error("Tank doesn't have a move component.");
		}
		return *mMoveComponent;
	}

	void TankBase::Update(WorldState& worldState)
	{
		GameObject::Update(worldState);

		worldState.mEntity = this->As<Entity>();

		worldState.mEntity = nullptr;
	}

	void TankBase::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);

		prescribedAttributeNames.PushBack(MOVE_COMP_NAME);
		prescribedAttributeNames.PushBack(SHOOT_COMP_NAME);
	}
}
