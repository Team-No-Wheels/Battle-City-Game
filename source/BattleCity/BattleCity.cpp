#include "Pch.h"
#include "BattleCity.h"
#include "ServiceLocator.h"
#include "World.h"

using namespace AnonymousEngine::Core;

namespace BattleCity
{
	BattleCity::BattleCity()
		:mLevelManager(), mWorld(nullptr)
	{
		ServiceLocator::AddService(ServiceLocator::sCollisionManager, mCollisionManager);
		//mSprite = new AnonymousEngine::Graphics::Sprite();
	}

	void BattleCity::Init()
	{
		//mSprite->Init("resources\\tank.png");

		//TODO comment it
		//mWorld = &mLevelManager.LoadWorld();		
		//mWorld->InitializeWorld();
	}

	void BattleCity::Update(float pDeltaTime)
	{
		pDeltaTime;
		//mWorld->Update();

		//mSprite->Render();
		//mSprite->Update(pDeltaTime);

		OutputDebugString("BattleCity : Update\n");
	}
}
