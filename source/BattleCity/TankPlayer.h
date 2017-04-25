#pragma once
#include "RTTI.h"
#include "TankBase.h"

namespace AnonymousEngine
{

	using namespace Containers;
	using namespace Core;

	class TankPlayer : public TankBase
	{

		RTTI_DECLARATIONS(TankPlayer, TankBase);

	public:

		TankPlayer();
		~TankPlayer();

		void IncrementLives();
		void DecrementLives();

		void IncrementStars();

		void SetInvincibility(bool state);
		bool IsInvincible();

		void Update(WorldState& worldState) override;

	private:
		std::uint32_t mLives, mMaxLives, mStars;
		std::chrono::milliseconds mTimeInvincible, mInvincbleLimit = std::chrono::milliseconds(2);
		bool mIsInvincible;
	};

	ENTITY_FACTORY_DECLARATIONS(TankPlayer);
	ENTITY_FACTORY_DEFINITIONS(TankPlayer);
}
