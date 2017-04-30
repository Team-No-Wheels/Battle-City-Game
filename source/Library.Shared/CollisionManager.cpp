#include "Pch.h"
#include "CollisionManager.h"
#include "GameObject.h"

namespace AnonymousEngine
{
	namespace Core
	{
		void CollisionManager::Update(Containers::WorldState& worldState)
		{
			worldState.mEntity = this;

			Vector<Collider*>::Iterator it = mColliders.begin();
			Vector<Collider*>::Iterator end = mColliders.end();
			Vector<Collider*>::Iterator current = it;

			for (; current != end; ++current)
			{
				for (it = current; it != end; ++it)
				{
					Collider& currentCollider = **current;
					Collider& otherCollider = **it;
					if (currentCollider.InCollision(otherCollider))
					{
						GameObject& currentObject = currentCollider.GetOwner();
						GameObject& otherObject = otherCollider.GetOwner();

						currentObject.OnCollision(otherObject);
						otherObject.OnCollision(currentObject);
					}
				}
			}
			
			worldState.mEntity = nullptr;
		}

		void CollisionManager::Register(Collider& collider)
		{
			mColliders.PushBack(&collider);
		}
	}
}