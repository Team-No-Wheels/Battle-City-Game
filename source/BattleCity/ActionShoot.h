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

		void PendKillBullet(Bullet& bullet);
		void DestroyBullet();

	private:
		bool mCanShoot, mIsEnemy;
		bool isFast, isDouble, isStrong; // For Star Power Up
		Vector<Bullet*> mBulletsLiving, mBulletsPending;
	};

	ACTION_FACTORY_DECLARATIONS(ActionShoot);
	ACTION_FACTORY_DEFINITIONS(ActionShoot);
}
