#pragma once

#include "TankBase.h"
#include "ActionFreeze.h"

namespace AnonymousEngine
{
	class BasicTankAI : public TankBase
	{
		ATTRIBUTED_DECLARATIONS(BasicTankAI, TankBase);

	public:

		BasicTankAI(const float speed = DEFAULT_SPEED, const int32_t bulletsNum = DEFAULT_BULLETS_NUM, const int32_t armor = DEFAULT_ARMOR);
		virtual ~BasicTankAI() = default;

		BasicTankAI(const BasicTankAI & rhs) = delete;
		BasicTankAI& operator=(const BasicTankAI& rhs) = delete;

		virtual void Update(WorldState& worldState) override;
		void HandleCollision();

		void Freeze();
		void Unfreeze();

	protected:

		ActionFreeze mActionFreeze;
		bool mIsFrozen;

		float mSpeed;
		int32_t mBulletsNum;
		int32_t mArmor;

		static const float DEFAULT_SPEED;
		static const int32_t DEFAULT_BULLETS_NUM;
		static const int32_t DEFAULT_ARMOR;
	};

	ENTITY_FACTORY_DECLARATIONS(BasicTankAI);
}
