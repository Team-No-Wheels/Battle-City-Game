#pragma once

#include "Entity.h"
#include "Sprite.h"
#include "glm/vec2.hpp"

namespace AnonymousEngine
{
	namespace Core
	{
		class GameObject : public Containers::Entity
		{
		public:
			GameObject();
			~GameObject() = default;
			
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
			//void OnCollision();
		protected:
		private:
			/**
			* The position of this game object in the world space.
			*/
			glm::vec4 mPosition;
			/**
			* The sprite representing this game object in the world.
			*/
			Graphics::Sprite mSprite;
			/** 
			* The attribute name for the member variable position.
			*/
			static const std::string sPositionAttributeName;

			ATTRIBUTED_DECLARATIONS(GameObject, Entity)
		};
	}
}