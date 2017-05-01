#include "Pch.h"
#include "TankAAI.h"

using namespace std;

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(TankAAI);
	ENTITY_FACTORY_DEFINITIONS(TankAAI);

	/************************************************************************/
	const float TankAAI::DEFAULT_SPEED = 1.0f;
	const int32_t TankAAI::DEFAULT_BULLETS_NUM = 1;
	const int32_t TankAAI::DEFAULT_ARMOR = 1;
	const uint32_t TankAAI::DEFAULT_PROB_TO_SHOOT_IN_MOV = 10;

	const string TankAAI::TYPE_NAME = "TankA";

	/************************************************************************/
	TankAAI::TankAAI(const float speed, const int32_t bulletsNum, const int32_t armor, const uint32_t probToShootInMov):
		BasicTankAI(speed, bulletsNum, armor, probToShootInMov)
	{
		mSpriteName = "Tank1_00";
	}

	/************************************************************************/
	std::string TankAAI::GetTankType()
	{
		return TYPE_NAME;
	}

	void TankAAI::Update(WorldState& worldState)
	{
		BasicTankAI::Update(worldState);
	}

	/************************************************************************/
	void TankAAI::AppendPrescribedAttributeNames(Vector<string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}
}
