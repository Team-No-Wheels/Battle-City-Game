#include "Pch.h"
#include "AnimatedSprite.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		AnimatedSprite::AnimatedSprite(Core::GameObject& pGameObject) :
			SpriteSheet(pGameObject), mFPS(10), mTimeElapsedSincePreviousFrame(0), mCurrentFrame(0), mIsAnimationLoop(true)
		{}

		AnimatedSprite::~AnimatedSprite()
		{
		}

		void AnimatedSprite::Init(const std::string& pSpriteFilePath)
		{
			SpriteSheet::Init(pSpriteFilePath);
		}

		void AnimatedSprite::Update(float pDeltaTime)
		{
			SpriteSheet::Update(pDeltaTime);

			mTimeElapsedSincePreviousFrame += pDeltaTime;

			if (mTimeElapsedSincePreviousFrame >= 1.0f / mFPS)
			{
				mTimeElapsedSincePreviousFrame = 0.0f;
				mCurrentFrame++;

				if (mCurrentFrame >= mSequence.Size())
				{
					mCurrentFrame = 0;
				}
				if(mCurrentFrame < mSequence.Size())
				{
					SetFrame(*mSequence[mCurrentFrame]);
				}
			}
		}

		void AnimatedSprite::AddFrame(Frame& pFrame)
		{
			mSequence.PushBack(&pFrame);
		}

		void AnimatedSprite::SetFPS(int pFPS)
		{
			mFPS = pFPS;
		}

		int AnimatedSprite::GetFPS()
		{
			return mFPS;
		}



	}
}