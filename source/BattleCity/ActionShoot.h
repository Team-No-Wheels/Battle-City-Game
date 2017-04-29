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

		RTTI_DECLARATIONS(ActionShoot, Action);

	public:

		ActionShoot();
		~ActionShoot();

		void Update(WorldState& worldState) override;
		void CreateBullet();
		void PendKillBullet(Bullet& bullet);
		void DestroyBullet();

		bool CanShoot() const;
		bool IsDouble() const;

	private:
		bool mCanShoot;
		bool isFast, isDouble, isStrong; // For Star Power Up
		Vector<Bullet*> mBulletsLiving, mBulletsPending;
	};

	ACTION_FACTORY_DECLARATIONS(ActionShoot);
}
