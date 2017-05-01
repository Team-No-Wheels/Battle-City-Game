#pragma once
#include "MessageInput.h"
#include "Action.h"
#include "EventSubscriber.h"
#include "Factory.h"

namespace AnonymousEngine
{

	using namespace Containers;
	using namespace Core;

	class Bullet;

	class ActionShoot : public Action
	{

		ATTRIBUTED_DECLARATIONS(ActionShoot, Action);

	public:

		ActionShoot(bool isPlayer = false);
		~ActionShoot() = default;

		void Update(WorldState& worldState) override;
		void CreateBullet();
		void KillBullet(Bullet& bullet);

		/** Return if shooting is currently possible
		*	@return True if shooting is currently possible
		*/
		bool CanShoot() const;

		/** Return whether the bullet was created by the player.
		*	@return True if the bullet was created by the player.
		*/
		bool IsOwnedByPlayer() const;

		/** Sets whether the bullet created will be fast
		*/
		void SetIsFast(const bool isFast);
		
		/** Sets whether the bullet created will be strong
		*/
		void SetIsStrong(const bool isStrong);

		/** Gets whether the bullet can shoot through metal.
		*	@return True if the bullet can shoot through metal.
		*/
		bool IsStrong() const;

		uint32_t GetCapacityToShoot() const;
		void SetCapacityToShoot(const uint32_t capacityToShoot);

	private:

		uint32_t mBulletsCapacity;
		bool mIsFast, mIsStrong; // For Star Power Up
		bool mIsOwnedByPlayer;
		Vector<Bullet*> mBulletsLiving;
	};

	ACTION_FACTORY_DECLARATIONS(ActionShoot);
}
