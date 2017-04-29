#pragma once

#include "RTTI.h"
#include "TankBase.h"
#include "EventSubscriber.h"

namespace AnonymousEngine
{
	using namespace Containers;
	using namespace Core;

	class TankPlayer : public TankBase, public EventSubscriber
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
		void Notify(class EventPublisher& publisher);

	private:
		std::uint32_t mLives, mMaxLives, mStars;
		std::chrono::milliseconds mTimeInvincible, mInvincbleLimit = std::chrono::milliseconds(2);
		bool mIsInvincible;
	};

	ENTITY_FACTORY_DECLARATIONS(TankPlayer);
}
