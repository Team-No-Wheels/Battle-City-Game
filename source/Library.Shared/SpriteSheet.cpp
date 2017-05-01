#include "Pch.h"
#include "SpriteSheet.h"
#include "ServiceLocator.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		SpriteSheet::SpriteSheet(Core::GameObject& pGameObject) :
			 Sprite(pGameObject), mCurrentFrameData(nullptr)
		{

		}

		SpriteSheet::~SpriteSheet()
		{

		}

		void SpriteSheet::Init(const std::string& pSpriteFilePath)
		{
			Sprite::Init(pSpriteFilePath);
		}

		void SpriteSheet::Update(float pDeltaTime)
		{
			Sprite::Update(pDeltaTime);

			if (!mCurrentFrameData)
			{
				mUVBounds.TopLeft.x = 0;
				mUVBounds.TopLeft.y = 0;

				mUVBounds.TopRight.x = 1;
				mUVBounds.TopRight.y = 0;

				mUVBounds.BottomLeft.x = 0;
				mUVBounds.BottomLeft.y = 1;

				mUVBounds.BottomRight.x = 1;
				mUVBounds.BottomRight.y = 1;
			}
			else
			{
				
			}
		}

		void SpriteSheet::Render() const
		{
			Sprite::Render();
		}

		void SpriteSheet::DrawDebugBounds() const
		{
			Sprite::DrawDebugBounds();
		}


		void SpriteSheet::SetFrame(Frame& pFrame)
		{
			mCurrentFrameData = &pFrame;

			mTexture = Core::ServiceLocator::GetTextureLoader()->GetTexture(mCurrentFrameData->mFilePath);
			mWidth = pFrame.width;
			mHeight = pFrame.height;

			mSpriteBounds.TopLeft.x = 0.0f;
			mSpriteBounds.TopLeft.y = (float)mHeight;

			mSpriteBounds.TopRight.x = (float)mWidth;
			mSpriteBounds.TopRight.y = (float)mHeight;

			mSpriteBounds.BottomLeft.x = 0.0f;
			mSpriteBounds.BottomLeft.y = 0.0f;

			mSpriteBounds.BottomRight.x = (float)mWidth;
			mSpriteBounds.BottomRight.y = 0.0f;

			// calculate UV
			// TODO : get the texture size from FramManager
			mUVBounds.TopLeft.x = mCurrentFrameData->mPosition.x / 128.0f;
			mUVBounds.TopLeft.y = (128.0f - mCurrentFrameData->mPosition.y - mCurrentFrameData->height) / 128.0f;

			mUVBounds.TopRight.x = (mCurrentFrameData->mPosition.x + mCurrentFrameData->width) / 128.0f;
			mUVBounds.TopRight.y = (128.0f - mCurrentFrameData->mPosition.y - mCurrentFrameData->height) / 128.0f;

			mUVBounds.BottomLeft.x = mCurrentFrameData->mPosition.x / 128.0f;
			mUVBounds.BottomLeft.y = (128.0f - mCurrentFrameData->mPosition.y) / 128.0f;

			mUVBounds.BottomRight.x = (mCurrentFrameData->mPosition.x + mCurrentFrameData->width) / 128.0f;
			mUVBounds.BottomRight.y = (128.0f - mCurrentFrameData->mPosition.y) / 128.0f;
		}


	}
}