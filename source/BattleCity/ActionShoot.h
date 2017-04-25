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

	class ActionShoot : public Action, public EventSubscriber
	{

		RTTI_DECLARATIONS(ActionShoot, Action);

	public:

		ActionShoot();
		~ActionShoot();

		void Update(WorldState& worldState);
		void CreateBullet();
		void Notify(class EventPublisher& publisher);

		void PendKillBullet();
		void DestroyBullet();

	private:
		bool mCanShoot, mIsEnemy, mBulletPendingKill;
		std::chrono::milliseconds mTimeLastShot, mShootFrequency; // For Enemy Ai
		Bullet* mCurBullet;
	};

	ACTION_FACTORY_DECLARATIONS(ActionShoot);
	ACTION_FACTORY_DEFINITIONS(ActionShoot);
}
