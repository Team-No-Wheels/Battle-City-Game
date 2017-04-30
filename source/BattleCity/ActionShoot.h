#pragma once
#include "MessageInput.h"
#include "Action.h"
#include "EventSubscriber.h"
#include "Bullet.h"
#include "Factory.h"

namespace AnonymousEngine
{

	using namespace Containers;
	using namespace Core;

	class ActionShoot : public Action
	{

		ATTRIBUTED_DECLARATIONS(ActionShoot, Action);

	public:

		ActionShoot();
		~ActionShoot() = default;

		void Update(WorldState& worldState) override;
		void CreateBullet();
		void PendKillBullet(Bullet& bullet);
		void DestroyPendingBullets();

		bool CanShoot() const;
		bool IsDouble() const;

		uint32_t GetCapacityToShoot() const;
		void SetCapacityToShoot(const uint32_t capacityToShoot);

	private:

		uint32_t mBulletsCapacity;
		bool isFast, isDouble, isStrong; // For Star Power Up
		Vector<Bullet*> mBulletsLiving, mBulletsPending;
	};

	ACTION_FACTORY_DECLARATIONS(ActionShoot);
}
