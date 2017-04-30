#include "Pch.h"
#include "BattleCity.h"
#include "ServiceLocator.h"

using namespace AnonymousEngine::Core;

namespace BattleCity
{
	BattleCity::BattleCity()
	{
		ServiceLocator::AddService(ServiceLocator::sCollisionManager, mCollisionManager);
		//mSprite = new AnonymousEngine::Graphics::Sprite();
	}

	void BattleCity::Init()
	{
		//mSprite->Init("resources\\tank.png");
	}

	void BattleCity::Update(float pDeltaTime)
	{
		pDeltaTime;
		//mSprite->Render();
		//mSprite->Update(pDeltaTime);

		OutputDebugString("BattleCity : Update\n");
	}
}
