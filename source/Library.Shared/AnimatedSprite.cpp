#include "Pch.h"
#include "AnimatedSprite.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		AnimatedSprite::AnimatedSprite(Core::GameObject& pGameObject) :
			SpriteSheet(pGameObject)
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


		}



	}
}