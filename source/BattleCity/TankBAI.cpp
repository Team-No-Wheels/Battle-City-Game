#include "Pch.h"
#include "TankBAI.h"

using namespace std;

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(TankBAI);
	ENTITY_FACTORY_DEFINITIONS(TankBAI);

	/************************************************************************/
	const float TankBAI::DEFAULT_SPEED = 3.0f;
	const int32_t TankBAI::DEFAULT_BULLETS_NUM = 1;
	const int32_t TankBAI::DEFAULT_ARMOR = 1;
	const uint32_t TankBAI::DEFAULT_PROB_TO_SHOOT_IN_MOV = 15;

	const string TankBAI::TYPE_NAME = "TankB";

	/************************************************************************/
	TankBAI::TankBAI(const float speed, const int32_t bulletsNum, const int32_t armor, const uint32_t probToShootInMov) :
		BasicTankAI(speed, bulletsNum, armor, probToShootInMov)
	{
	}

	/************************************************************************/
	std::string TankBAI::GetTankType()
	{
		return TYPE_NAME;
	}
}
