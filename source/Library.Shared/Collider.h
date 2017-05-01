#pragma once

#include <cstdint>

namespace AnonymousEngine
{
	namespace Core
	{
		class GameObject;
		class Collider
		{
		public:
			/**
			* Constructor - Registers the collider to the collision manager.
			* @param gameObject The game object to which this collider belongs.
			*/
			Collider(Core::GameObject& gameObject);
			/**
			* Destructor - Unregister the collider from the collision manager.
			*/
			/**
			*
			*/
			~Collider();
			/**
			* An enum represent the tags a collider could take.
			*/
			enum class ColliderTag
			{
				Invalid,
				Player,
				Enemy,
				PlayerBullet,
				EnemyBullet,
				Wall,
				Destructable,
				MuricanEagle
			};

			/**
			* Set the collider tag.
			*/
			void SetTag(const ColliderTag& tag);
			/**
			* Get the collider tag.
			*/
			const ColliderTag& GetTag() const;
			/**
			* Set the dimensions of this collider.
			* Length along x-axis.
			* Length along y-axis.
			*/
			void SetDimensions(const std::int32_t& width, const std::int32_t& height);
			/**
			* Check if this collider is in collision with another.
			* @param otherCollider The collider to check for collision with.
			* @return True if the collision occured.
			*/
			bool InCollision(Collider& otherCollider) const;
			/**
			* Get a reference to the game object associated with this collider.
			*/
			GameObject& GetOwner();
		private:
			/**
			* The game object which owns this collider.
			*/
			Core::GameObject& mGameObject;
			/**
			* Collider tag.
			*/
			ColliderTag mColliderTag;
			/**
			* The length of the collider along x-axis.
			*/
			std::int32_t mWidth;
			/**
			* The length of the collider along y-axis.
			*/
			std::int32_t mHeight;
		};
	}
}