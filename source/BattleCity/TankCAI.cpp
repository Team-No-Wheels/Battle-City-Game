#include "Pch.h"
#include "TankCAI.h"

using namespace std;

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(TankCAI);
	ENTITY_FACTORY_DEFINITIONS(TankCAI);

	/************************************************************************/
	const float TankCAI::DEFAULT_SPEED = 1.0f;
	const int32_t TankCAI::DEFAULT_BULLETS_NUM = 1;
	const int32_t TankCAI::DEFAULT_ARMOR = 1;
	const uint32_t TankCAI::DEFAULT_PROB_TO_SHOOT_IN_MOV = 10;

	const string TankCAI::TYPE_NAME = "TankC";

	/************************************************************************/
	TankCAI::TankCAI(const float speed, const int32_t bulletsNum, const int32_t armor, const uint32_t probToShootInMov) :
		BasicTankAI(speed, bulletsNum, armor, probToShootInMov)
	{
	}

	/************************************************************************/
	std::string TankCAI::GetTankType()
	{
		return TYPE_NAME;
	}
}
