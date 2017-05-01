#include "Pch.h"
#include "BattleCity.h"
#include "ServiceLocator.h"
#include "World.h"
#include "SpriteSheet.h"
#include "AnimatedSprite.h"
#include "MessageAudio.h"
#include "Event.h"

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
		mAudio.Initialize();
		mWorld = &mLevelManager.LoadWorld();
		mWorld->InitializeWorld();
		mLevelManager.LoadLevelTiles(mWorld->GetWorldState().GetCurrentLevel());
	}

	void BattleCity::Update()
	{
		mGameClock.UpdateGameTime(mWorld->GetWorldState().mGameTime);
		mWorld->Update();
		mInputHandler.Update(mWorld->GetWorldState());
	}

	AnonymousEngine::InputHandler& BattleCity::InputHandler()
	{
		return mInputHandler;
	}
}