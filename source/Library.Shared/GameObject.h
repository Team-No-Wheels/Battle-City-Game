#pragma once

#include "Entity.h"
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

			void SetPosition(const glm::vec2& position);
			const glm::vec2& GetPosition() const;
		protected:
		private:
			/**
			* The position of this game object in the world space.
			*/
			glm::vec2 mPosition;

			ATTRIBUTED_DECLARATIONS(GameObject, Entity)
		};
	}
}