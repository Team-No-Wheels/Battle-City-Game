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

		void IncrementStars();

		void SetInvincibility(bool state);
		bool IsInvincible() const;

		void Update(WorldState& worldState) override;
		void Notify(class EventPublisher& publisher) override;

	private:
		std::uint32_t mStars;
		std::chrono::milliseconds mTimeInvincible, mInvincbleLimit = std::chrono::milliseconds(2);
		bool mIsInvincible;
	};

	ENTITY_FACTORY_DECLARATIONS(TankPlayer);
}
