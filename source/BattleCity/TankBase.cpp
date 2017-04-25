#include "Pch.h"
#include "TankBase.h"

using namespace AnonymousEngine;
RTTI_DEFINITIONS(TankBase);

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