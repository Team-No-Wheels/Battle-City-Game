#include "Pch.h"
#include "TankDAI.h"

using namespace std;

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(TankDAI);
	ENTITY_FACTORY_DEFINITIONS(TankDAI);

	/************************************************************************/
	const float TankDAI::DEFAULT_SPEED = 0.5f;
	const int32_t TankDAI::DEFAULT_BULLETS_NUM = 1;
	const int32_t TankDAI::DEFAULT_ARMOR = 4;
	const uint32_t TankDAI::DEFAULT_PROB_TO_SHOOT_IN_MOV = 15;

	const string TankDAI::TYPE_NAME = "TankD";

	/************************************************************************/
	TankDAI::TankDAI(const float speed, const int32_t bulletsNum, const int32_t armor, const uint32_t probToShootInMov) :
		BasicTankAI(speed, bulletsNum, armor, probToShootInMov)
	{
	}

	/************************************************************************/
	std::string TankDAI::GetTankType()
	{
		return TYPE_NAME;
	}
}
