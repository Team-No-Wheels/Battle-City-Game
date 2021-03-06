#include "Pch.h"
#include "GameObject.h"
#include "World.h"
#include "SpriteSheet.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	namespace Core
	{
		const std::string GameObject::sPositionAttributeName = "Position";
		const std::string GameObject::sWidthAttributeName = "width";
		const std::string GameObject::sHeightAttributeName = "height";

		GameObject::GameObject() : 
			mPosition(std::move(glm::vec4())), mSprite(nullptr), mCollider(*this)
		{
			AddExternalAttribute(sPositionAttributeName, &mPosition, 1);
			AddExternalAttribute("SpriteName", &mSpriteName, 1);
		}

		void GameObject::SetPosition(const glm::vec4& position)
		{
			mPosition = position;

			mSprite->UpdatePosition();
		}

		const glm::vec4& GameObject::GetPosition() const
		{
			return mPosition;
		}

		void GameObject::Update(Containers::WorldState& worldState)
		{
			Entity::Update(worldState);
			worldState.mEntity = this;
			// Handle if the object is marked for delete
			if (mMarkedForDelete)
			{
				AddToDeleteQueue(worldState);
				return;
			}

			if (mSprite)
			{
				mSprite->UpdatePosition();

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

		void GameObject::SetMarkForDelete(bool value)
		{
			mMarkedForDelete = value;
		}

		AnonymousEngine::Containers::WorldState* GameObject::GetWorldState() const
		{
			static AnonymousEngine::Containers::WorldState* state = nullptr;
			if (state == nullptr)
			{
				// Loop Through Parent To Find World
				auto parent = GetParent();
				while (parent != nullptr)
				{
					parent = parent->GetParent();

					// If World, Return WorldState
					if (parent->Is(Containers::World::TypeIdClass()))
					{
						state = &parent->As<Containers::World>()->GetWorldState();
					}
				}
			}

			return state;
		}

		void GameObject::SetRotation(float pAngle)
		{
			mRotation = pAngle;

			mSprite->UpdateRotation();
		}

		float GameObject::GetRotation()
		{
			return mRotation;
		}

		void GameObject::AddToDeleteQueue(Containers::WorldState& worldState)
		{
			worldState.mWorld->MarkForDelete(*this);
			worldState.mEntity = nullptr;
		}

		void GameObject::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);

			prescribedAttributeNames.PushBack("Position");
			prescribedAttributeNames.PushBack("SpriteName");
			prescribedAttributeNames.PushBack("width");
			prescribedAttributeNames.PushBack("height");
		}

		Graphics::Color GameObject::GetTint()
		{
			return mTint;
		}

		ATTRIBUTED_DEFINITIONS(GameObject)
	}
}
