#include "Pch.h"
#include "GameObject.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		GameObject::GameObject() : mPosition(std::move(glm::vec4()))
		{

		}

		void GameObject::SetPosition(const glm::vec4& position)
		{
			mPosition = position;
		}

		const glm::vec4& GameObject::GetPosition() const
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