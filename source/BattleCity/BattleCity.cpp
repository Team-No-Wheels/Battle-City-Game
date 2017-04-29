#include "Pch.h"
#include "BattleCity.h"

namespace BattleCity
{
	BattleCity::BattleCity()
	{
		mSprite = new AnonymousEngine::Graphics::Sprite();
	}

	void BattleCity::Init()
	{
		mSprite->Init("resources/tank.png");
	}

	void BattleCity::Update(float pDeltaTime)
	{
		pDeltaTime;
		mSprite->Render();
		mSprite->Update(pDeltaTime);

		OutputDebugString("BattleCity : Update\n");
	}
}