#include "Pch.h"
#include "BattleCity.h"
#include "ServiceLocator.h"
#include "World.h"
#include "SpriteSheet.h"

#include "MessageAudio.h"
#include "Event.h"


using namespace AnonymousEngine::Core;

namespace BattleCity
{
	BattleCity::BattleCity()
		:mLevelManager(), mWorld(nullptr), mTestAudio(false)
	{
		ServiceLocator::AddService(ServiceLocator::sCollisionManager, mCollisionManager);
		
		//mSprite = new AnonymousEngine::Graphics::Sprite();
		//ServiceLocator::GetTextureLoader()->GetTexture("resources\\tank.png");
		mGameObject = new AnonymousEngine::Core::GameObject();
		AnonymousEngine::Graphics::SpriteSheet* spritesheet = new AnonymousEngine::Graphics::SpriteSheet(*mGameObject);

		AnonymousEngine::Graphics::Frame* frame = new AnonymousEngine::Graphics::Frame;
		frame->mFilePath = "resources\\General.png";
		frame->mFrameID = 1;
		frame->mFrameName = "";
		frame->mPosition = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		frame->width = 15;
		frame->height = 15;

		spritesheet->SetFrame(*frame);
		mGameObject->SetPosition(glm::vec4(100.0f, 100.0f, 0.0f, 0.0f));
	}

	void BattleCity::Init()
	{
		mAudio.Initialize();
		//mWorld = &mLevelManager.LoadWorld();
		//mWorld->InitializeWorld();
		//mLevelManager.LoadLevelTiles(mWorld->GetWorldState().GetCurrentLevel());
		mGameObject->GetSprite().Init("resources\\General.png");
	}

	void BattleCity::Update()
	{
		//Audio Test
		if (!mTestAudio)
		{
			mTestAudio = true;
			AnonymousEngine::Audio::MessageAudio message;
			message.SetAudioType("PowerUpBomb");
			AnonymousEngine::Core::Event<AnonymousEngine::Audio::MessageAudio> event = message;
			event.Deliver();
		}
		//mGameClock.UpdateGameTime(mWorld->GetWorldState().mGameTime);
		//mWorld->Update();

		//mSprite->Render();
		//mSprite->Update(pDeltaTime);
		
		//mGameObject->SetPosition(mGameObject->GetPosition() + glm::vec4(0.0f, -1.0f, 0.0f, 0.0f) * pDeltaTime);

		mGameObject->GetSprite().Render();
		mGameObject->GetSprite().Update(1.0f / 60.0f);

		OutputDebugString("BattleCity : Update\n");
	}
}