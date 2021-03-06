#pragma once

#include "BasicTankAI.h"

namespace AnonymousEngine
{
	class TankCAI : public BasicTankAI
	{
		ATTRIBUTED_DECLARATIONS(TankCAI, BasicTankAI);

	public:

		/** TankCAI constructor.
		*/
		explicit TankCAI(const float speed = DEFAULT_SPEED, const int32_t bulletsNum = DEFAULT_BULLETS_NUM,
						 const int32_t armor = DEFAULT_ARMOR, const uint32_t probToShootInMov = DEFAULT_PROB_TO_SHOOT_IN_MOV);

		virtual ~TankCAI() = default;

		virtual std::string GetTankType() override;

	private:

		static const float DEFAULT_SPEED;
		static const int32_t DEFAULT_BULLETS_NUM;
		static const int32_t DEFAULT_ARMOR;
		static const uint32_t DEFAULT_PROB_TO_SHOOT_IN_MOV;

		static const std::string TYPE_NAME;

	};

	ENTITY_FACTORY_DECLARATIONS(TankCAI);
}
