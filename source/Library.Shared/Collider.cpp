#include "Collider.h"
#include "glm/glm.hpp"
#include "GameObject.h"

using namespace AnonymousEngine::Core;

namespace AnonymousEngine
{
	Collider::Collider(GameObject& gameObject) : mGameObject(gameObject), mColliderTag(ColliderTag::Invalid), mHeight(0), mWidth(0)
	{

	}

	void Collider::SetTag(const Collider::ColliderTag& tag)
	{
		mColliderTag = tag;
	}

	const Collider::ColliderTag& Collider::GetTag() const
	{
		return mColliderTag;
	}

	void Collider::SetDimensions(const std::int32_t& width, const std::int32_t& height)
	{
		mWidth = width;
		mHeight = height;
	}

	bool Collider::InCollision(Collider& otherCollider) const
	{
		const glm::vec4& ownerPosition = mGameObject.GetPosition();
		const glm::vec4& otherPosition = otherCollider.GetOwner().GetPosition();
		// Get the centers of both the game objects
		float thisX = ownerPosition.x;
		float thisY = ownerPosition.y;
		float otherX = otherPosition.x;
		float otherY = otherPosition.y;
		// Get the bottom left corners of both the game objects (For the pivot at the center)
		thisX -= (mWidth / 2);
		thisY -= (mHeight / 2);
		otherX -= (otherCollider.mWidth / 2);
		otherY -= (otherCollider.mHeight / 2);
		// Check for collision
		if ((thisX >= otherX && thisX <= (otherX + otherCollider.mWidth)) || (((thisX + mWidth) >= otherX) && (thisX + mWidth) <= (otherX + otherCollider.mWidth)))
		{
			if (((thisY >= otherY) && thisY <= (otherY + otherCollider.mHeight)) || ((thisY + mHeight) >= otherY) && (thisY + mHeight >= otherY + otherCollider.mHeight))
			{
				return true;
			}
		}
		return false;
	}

	GameObject& Collider::GetOwner()
	{
		return mGameObject;
	}
}