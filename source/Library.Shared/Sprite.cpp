#include "Pch.h"
#include "Sprite.h"
#include "ServiceLocator.h"
#include "GameObject.h"

//#include "TextureLoader.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		Sprite::Sprite(Core::GameObject& pGameObject) : 
			mGameObject(pGameObject), mUVBounds(0, 0, 1, 0, 0, 1, 1, 1)
		{
			mGameObject.SetSprite(*this);

			mGameObject.AddExternalAttribute(Core::GameObject::sWidthAttributeName, &mWidth, 1);
			mGameObject.AddExternalAttribute(Core::GameObject::sHeightAttributeName, &mHeight, 1);
		}


		void Sprite::Init(const std::string& pSpriteFilePath)
		{
			Renderable::Init(pSpriteFilePath);
			TextureLoaderService* loader = Core::ServiceLocator::GetTextureLoader();
			mTexture = loader->GetTexture(pSpriteFilePath);

			mHeight = 15;
			mWidth = 15;

			mSpriteBounds.TopLeft.x = 0.0f;
			mSpriteBounds.TopLeft.y = (float)mHeight;

			mSpriteBounds.TopRight.x = (float)mWidth;
			mSpriteBounds.TopRight.y = (float)mHeight;

			mSpriteBounds.BottomLeft.x = 0.0f;
			mSpriteBounds.BottomLeft.y = 0.0f;

			mSpriteBounds.BottomRight.x = (float)mWidth;
			mSpriteBounds.BottomRight.y = 0.0f;
		}

		void Sprite::Update(float pDeltaTime)
		{
			Renderable::Update(pDeltaTime);
		}

		void Sprite::Render() const
		{
			if (isInitialized)
			{
				Core::ServiceLocator::GetRenderer()->Render(*this);

#ifdef _DEBUG
				DrawDebugBounds();
#endif 
			}
		}

		void Sprite::DrawDebugBounds() const
		{
			Core::ServiceLocator::GetRenderer()->DrawRectangle(GetSpriteBounds(), 255, 0, 0);
		}

		Core::GameObject& Sprite::GetOwner() const
		{
			return mGameObject;
		}

		Geometry::Rectangle Sprite::GetSpriteBounds() const
		{
			// translate the bounds to sprite position
			glm::vec4 translationValue = GetOwner().GetPosition() - glm::vec4(GetWidth() / 2.0f, GetHeight() / 2.0f, 0.0f, 0.0f);
			return Geometry::Rectangle::Translate(mSpriteBounds, translationValue);
		}

		const Geometry::Rectangle& Sprite::GetUVBounds() const
		{
			return mUVBounds;
		}
	}
}