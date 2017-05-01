#include "Pch.h"
#include "BattleCity.h"
#include "ServiceLocator.h"
#include "World.h"

#include "MessageAudio.h"
#include "Event.h"


using namespace AnonymousEngine::Core;

namespace BattleCity
{
	BattleCity::BattleCity()
		:mLevelManager(), mWorld(nullptr), mTestAudio(false)
	{
		ServiceLocator::AddService(ServiceLocator::sCollisionManager, mCollisionManager);
	}

	void BattleCity::Init()
	{
		mWorld = &mLevelManager.LoadWorld();
		mWorld->InitializeWorld();
		mLevelManager.LoadLevelTiles(mWorld->GetWorldState().GetCurrentLevel());
		mAudio.Initialize();
	}

	void BattleCity::Update()
	{
		mGameClock.UpdateGameTime(mWorld->GetWorldState().mGameTime);
		mWorld->Update();

		//Audio Test
		if (!mTestAudio)
		{
			mTestAudio = true;
			AnonymousEngine::Audio::MessageAudio message;
			message.SetAudioType("PowerUpBomb");
			AnonymousEngine::Core::Event<AnonymousEngine::Audio::MessageAudio> event = message;
			event.Deliver();
		}

		OutputDebugString("BattleCity : Update\n");
	}
}