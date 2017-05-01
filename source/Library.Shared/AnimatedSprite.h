#pragma once
#include "SpriteSheet.h"
#include "Vector.h"
#include "Frame.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		class AnimatedSprite : public SpriteSheet
		{
		public:
			AnimatedSprite(Core::GameObject& pGameObject);
			~AnimatedSprite();

			/**
				@brief Call Init with the file name will initialize this Renderable object with the file.
				@param[in] pFilePath Constant reference to string that holds the path of the file.
			*/
			virtual void Init(const std::string& pSpriteFilePath) override;

			/**
				@brief Called every frame.
				@param[in] pDeltaTime Time between frames in seconds.
			*/
			virtual void Update(float pDeltaTime) override;

			void AddFrame(Frame& pFrame);

			void SetFPS(int pFPS);

			int GetFPS();
		protected:
			/**
				Sequence of frames for animation
			*/
			Vector<Frame*> mSequence;

			int mFPS;

			float mTimeElapsedSincePreviousFrame;
			std::uint32_t mCurrentFrame;
			bool mIsAnimationLoop = true;
		};
	}
}