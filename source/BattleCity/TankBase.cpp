#include "Pch.h"
#include "TankBase.h"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(TankBase);

	const std::string TankBase::sMoveComponentName = "MoveComponent";
	const std::string TankBase::sShootComponentName = "ShootComponent";

	TankBase::TankBase() :
		mMoveComponent(nullptr), //CreateAction(sMoveComponentName, "ActionMove").As<ActionMove>()),
		mShootComponent(nullptr) //(CreateAction(sShootComponentName, "ActionShoot").As<ActionShoot>())
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
	}
}
