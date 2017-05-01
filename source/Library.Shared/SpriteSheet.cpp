#include "Pch.h"
#include "SpriteSheet.h"
#include "ServiceLocator.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		SpriteSheet::SpriteSheet(Core::GameObject& pGameObject) :
			 Sprite(pGameObject), mFrameData(nullptr)
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

			if (!mFrameData)
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
			mFrameData = &pFrame;

			mTexture = Core::ServiceLocator::GetTextureLoader()->GetTexture(mFrameData->mFilePath);

			// calculate UV
			// TODO : get the texture size from FramManager
			mUVBounds.TopLeft.x = mFrameData->mPosition.x / 128.0f;
			mUVBounds.TopLeft.y = (128.0f - mFrameData->mPosition.y - mFrameData->height) / 128.0f;

			mUVBounds.TopRight.x = (mFrameData->mPosition.x + mFrameData->width) / 128.0f;
			mUVBounds.TopRight.y = (128.0f - mFrameData->mPosition.y - mFrameData->height) / 128.0f;

			mUVBounds.BottomLeft.x = mFrameData->mPosition.x / 128.0f;
			mUVBounds.BottomLeft.y = (128.0f - mFrameData->mPosition.y) / 128.0f;

			mUVBounds.BottomRight.x = (mFrameData->mPosition.x + mFrameData->width) / 128.0f;
			mUVBounds.BottomRight.y = (128.0f - mFrameData->mPosition.y) / 128.0f;
		}


	}
}