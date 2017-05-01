#include "Pch.h"
#include "BattleCity.h"
#include "ServiceLocator.h"
#include "World.h"
#include "SpriteSheet.h"

using namespace AnonymousEngine::Core;
//
using namespace AnonymousEngine::Containers;

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
	}
}
