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
		ATTRIBUTED_DECLARATIONS(TankPlayer, TankBase);

	public:

		TankPlayer();
		~TankPlayer();

		void IncrementStars();

		void SetInvincibility(bool onRespawn);
		bool IsInvincible() const;

		void Update(WorldState& worldState) override;
		void Notify(class EventPublisher& publisher) override;

		virtual void OnCollision(GameObject& otherGameObject) override;

		void Respawn();

	private:
		std::uint32_t mStars;
		std::chrono::milliseconds mTimeInvincible;
		bool mIsInvincible;

		static const std::chrono::milliseconds sInvincbleLimitOnRespawn;
		static const std::chrono::milliseconds sInvincbleLimitOnPoweUp;
	};

	ENTITY_FACTORY_DECLARATIONS(TankPlayer);
}
