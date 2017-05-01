#include "Pch.h"
#include "GameObject.h"
#include "World.h"
#include "SpriteSheet.h"

namespace AnonymousEngine
{
	namespace Core
	{
		const std::string GameObject::sPositionAttributeName = "Position";
		const std::string GameObject::sWidthAttributeName = "width";
		const std::string GameObject::sHeightAttributeName = "height";

		GameObject::GameObject() : 
			mPosition(std::move(glm::vec4())), mCollider(*this), mSprite(nullptr)
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

			if (mSprite)
			{
				// sprite render and update.
				mSprite->Render();
				//mSprite->Update(worldState.mGameTime.ElapsedGameTime().count());
				mSprite->Update(1.0f / 60.0f);
			}
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

		void GameObject::SetSprite(Graphics::Sprite& pSprite)
		{
			mSprite = &pSprite;
		}

		Graphics::Sprite& GameObject::GetSprite()
		{
			return *mSprite;
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
			prescribedAttributeNames.PushBack(sWidthAttributeName);
			prescribedAttributeNames.PushBack(sHeightAttributeName);
		}

		ATTRIBUTED_DEFINITIONS(GameObject)
	}
}