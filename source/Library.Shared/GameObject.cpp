#include "Pch.h"
#include "GameObject.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		GameObject::GameObject() : mPosition(std::move(glm::vec2(0,0)))
		{

		}

		void GameObject::SetPosition(const glm::vec2& position)
		{
			mPosition = position;
		}

		const glm::vec2& GameObject::GetPosition() const
		{
			return mPosition;
		}

		void GameObject::Update(WorldState& worldState)
		{
			worldState;
		}

		ATTRIBUTED_DEFINITIONS(GameObject)
	}
}