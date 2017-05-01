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
			mGameObject(pGameObject), mUVBounds(0, 1, 1, 1, 0, 0, 1, 0)
		{

		}


		void Sprite::Init(const std::string& pSpriteFilePath)
		{
			Renderable::Init(pSpriteFilePath);
			TextureLoaderService* loader = Core::ServiceLocator::GetTextureLoader();
			mTexture = loader->GetTexture(pSpriteFilePath);

			mHeight = 100;
			mWidth = 100;

			mSpriteBounds.TopLeft.x = 0.0f;
			mSpriteBounds.TopLeft.y = (float)mHeight;

			mSpriteBounds.TopRight.x = (float)mWidth;
			mSpriteBounds.TopRight.y = (float)mHeight;

			mSpriteBounds.BottomLeft.x = 0.0f;
			mSpriteBounds.BottomLeft.y = 0.0f;

			mSpriteBounds.BottomRight.x = (float)mWidth;
			mSpriteBounds.BottomRight.y = 0.0f;

			//glClearColor(backRed, backGreen, backGreen, 0.0f);			// Background Color
			glClearDepth(1.0f);											// Depth Buffer Setup

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending
			glEnable(GL_BLEND);											// Enable Blending
			glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
			glEnable(GL_CULL_FACE);										// Remove Back Face
			//glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);										// Type Of Depth Testing
		}

		void Sprite::Update(float pDeltaTime)
		{
			Renderable::Update(pDeltaTime);
		}

		void Sprite::Render()
		{
			if (isInitialized)
			{
				Core::ServiceLocator::GetRenderer()->Render(mTexture, Geometry::Rectangle::Translate(mSpriteBounds, mGameObject.GetPosition()), mUVBounds);

#ifdef _DEBUG
				DrawDebugBounds();
#endif 
			}
		}

		void Sprite::DrawDebugBounds()
		{
			Core::ServiceLocator::GetRenderer()->DrawRectangle(Geometry::Rectangle::Translate(mSpriteBounds, mGameObject.GetPosition()), 255, 0, 0);
		}

		Core::GameObject& Sprite::GetOwner()
		{
			return mGameObject;
		}
	}
}