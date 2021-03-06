#pragma once

#include "Entity.h"
#include "Sprite.h"
#include "Collider.h"
#include "glm/glm.hpp"
#include "Color.h"

namespace AnonymousEngine
{
	namespace Core
	{
		class GameObject : public Containers::Entity
		{
			friend class Graphics::Sprite;

		public:
			/**
			* Initialize a game object
			*/
			GameObject();

			/**
			* Default destructor
			*/
			virtual ~GameObject() = default;
			
			/**
			* Set the position of this game object.
			* @param position The position to set.
			*/
			void SetPosition(const glm::vec4& position);
			/**
			* Get the position of this game object.
			*/
			const glm::vec4& GetPosition() const;
			/**
			* Override to the Update call for entity.
			*/
			virtual void Update(Containers::WorldState& worldState) override;
			/**
			* The method called in case of a collision of this game object with another.
			*/
			virtual void OnCollision(GameObject& otherGameObject);
			/**
			* Get a reference to the collider contained within this game object.
			*/
			Collider& GetCollider();

			/**
				@brief set the sprite
			*/
			void SetSprite(Graphics::Sprite& pSprite);

			/**
			* Get a reference to the sprite contained within this game object.
			*/
			Graphics::Sprite& GetSprite();
			/**
			* Set whether an game object should be deleted or not before next Update call.
			*/
			void SetMarkForDelete(bool value = true);

			/**
				@brief Set rotation
				@param[in] pAngle Angle in degree.
			*/
			void SetRotation(float pAngle);
			/**
				@brief get rotation.
			*/
			float GetRotation();

			Graphics::Color GetTint();

		protected:

			class AnonymousEngine::Containers::WorldState* GetWorldState() const;

			void AddToDeleteQueue(Containers::WorldState& worldState);
			/**
			* The position of this game object in the world space.
			*/
			glm::vec4 mPosition;
			/** The name of the sprite to query from frame manager
			*/
			std::string mSpriteName;
			/**
				Rotation of the game object.
			*/
			float mRotation;
			/**
			* The sprite representing this game object in the world.
			*/
			Graphics::Sprite* mSprite;
			/**
			* The collider associated with this game object.
			*/
			Collider mCollider;
			/**
			* Whether this game object is marked for delete.
			*/
			bool mMarkedForDelete;
			
			Graphics::Color mTint;

			/** 
			* The attribute name for the member variable position.
			*/
			static const std::string sPositionAttributeName;
			static const std::string sWidthAttributeName;
			static const std::string sHeightAttributeName;

			ATTRIBUTED_DECLARATIONS(GameObject, Entity)
		};
	}
}