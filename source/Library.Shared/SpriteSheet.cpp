#include "Pch.h"
#include "SpriteSheet.h"


namespace AnonymousEngine
{
	namespace Graphics
	{
		SpriteSheet::SpriteSheet(Core::GameObject& pGameObject) :
			 Sprite(pGameObject)
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
		}

		void SpriteSheet::Render()
		{
			Sprite::Render();
		}

		void SpriteSheet::DrawDebugBounds()
		{
			Sprite::DrawDebugBounds();
		}


	}
}