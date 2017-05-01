#include "Pch.h"
#include "TankBase.h"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(TankBase);

	TankBase::TankBase() :
		mMoveComponent(CreateAction("ActionMove", "ActionMove").As<ActionMove>()),
		mShootComponent(CreateAction("ActionShoot", "ActionShoot").As<ActionShoot>())
	{

	}

	TankBase::~TankBase()
	{

	}

	ActionMove& TankBase::MoveComponent()
	{
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
