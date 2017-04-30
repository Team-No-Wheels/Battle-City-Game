#pragma once

#include "Entity.h"
#include "Vector.h"
#include "Collider.h"

namespace AnonymousEngine
{
	namespace Core
	{
		class CollisionManager : public Containers::Entity
		{
		public:
			/**
			* Iterates over the colliders to check for collision and call their OnCollision methods accordingly.
			*/
			virtual void Update(Containers::WorldState& worldState) override;
			/**
			* Register a collider to the collision manager.
			* @param collider The collider to register to the collision manager.
			*/
			void Register(Collider& collider);
		private:
			Vector<Collider*> mColliders;
		};
	}
}