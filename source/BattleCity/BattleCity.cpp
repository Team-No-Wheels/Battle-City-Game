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
	}

	void BattleCity::Init()
	{
		mWorld = &mLevelManager.LoadWorld();
		mWorld->InitializeWorld();
		mLevelManager.LoadLevelTiles(mWorld->GetWorldState().GetCurrentLevel());
	}

	void BattleCity::Update()
	{
		mGameClock.UpdateGameTime(mWorld->GetWorldState().mGameTime);
		mWorld->Update();
		OutputDebugString("BattleCity : Update\n");
	}
}
