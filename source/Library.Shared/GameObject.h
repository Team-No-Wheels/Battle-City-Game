#pragma once

#include "Entity.h"
#include "Sprite.h"
#include "glm/vec2.hpp"

namespace AnonymousEngine
{
	namespace Containers
	{
		class GameObject : public Entity
		{
		public:
			GameObject();
			~GameObject() = default;
			
			/**
			* Set the position of this game object.
			* @param position The position to set.
			*/
			void SetPosition(const glm::vec2& position);
			/**
			* Get the position of this game object.
			*/
			const glm::vec2& GetPosition() const;
			/**
			* Override to the Update call for entity.
			*/
			virtual void Update(WorldState& worldState) override;
		protected:
		private:
			/**
			* The position of this game object in the world space.
			*/
			glm::vec2 mPosition;
			/**
			* The sprite representing this game object in the world.
			*/
			Graphics::Sprite mSprite;

			ATTRIBUTED_DECLARATIONS(GameObject, Entity)
		};
	}
}