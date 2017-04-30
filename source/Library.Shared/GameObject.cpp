#include "Pch.h"
#include "GameObject.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		const std::string sPositionAttributeName = "Position";

		GameObject::GameObject() : mPosition(std::move(glm::vec4()))
		{
			AddExternalAttribute(sPositionAttributeName, &mPosition, 1);
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

		void GameObject::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack(sPositionAttributeName);
		}

		ATTRIBUTED_DEFINITIONS(GameObject)
	}
}