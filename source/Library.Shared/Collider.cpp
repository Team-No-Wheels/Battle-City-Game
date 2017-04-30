#include "Collider.h"

using namespace AnonymousEngine::Core;

namespace AnonymousEngine
{
	Collider::Collider(GameObject& gameObject) : mGameObject(gameObject), mColliderTag(ColliderTag::Invalid), mHeight(0), mLength(0)
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
	
	void Collider::SetDimensions(const std::int32_t& length, const std::int32_t& height)
	{
		mLength = length;
		mHeight = height;
	}
	
	bool Collider::InCollision(const Collider& otherCollider)
	{
		// TODO Implement
		otherCollider;
		return false;
	}
	
	Core::GameObject& Core::Collider::GetOwner()
	{
		return mGameObject;
	}
}