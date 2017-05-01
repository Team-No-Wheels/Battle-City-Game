#include "Pch.h"
#include "GameObject.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Core
	{
		const std::string GameObject::sPositionAttributeName = "Position";

		GameObject::GameObject() : mPosition(std::move(glm::vec4())), mCollider(*this), mSprite(*this)
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

		void GameObject::Update(Containers::WorldState& worldState)
		{
			worldState.mEntity = this;
			// Handle if the object is marked for delete
			if (mMarkedForDelete)
			{
				AddToDeleteQueue(worldState);
				return;
			}
			// sprite render and update.
			mSprite.Render();
			mSprite.Update(1.0f / 60.0f);

			worldState.mEntity = nullptr;
		}

		void GameObject::OnCollision(GameObject& otherGameObject)
		{
			otherGameObject;
		}

		Collider& GameObject::GetCollider()
		{
			return mCollider;
		}

		Graphics::Sprite& GameObject::GetSprite()
		{
			return mSprite;
		}

		void GameObject::SetMarkForDelete(bool value /* = true */)
		{
			mMarkedForDelete = value;
		}

		void GameObject::AddToDeleteQueue(Containers::WorldState& worldState)
		{
			worldState.mWorld->MarkForDelete(*this);
			worldState.mEntity = nullptr;
		}

		void GameObject::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack(sPositionAttributeName);
		}

		ATTRIBUTED_DEFINITIONS(GameObject)
	}
}