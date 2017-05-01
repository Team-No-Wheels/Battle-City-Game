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
		:mLevelManager(), mWorld(nullptr), mTestAudio(false)
	{
		ServiceLocator::AddService(ServiceLocator::sCollisionManager, mCollisionManager);
		
		//mSprite = new AnonymousEngine::Graphics::Sprite();
		//ServiceLocator::GetTextureLoader()->GetTexture("resources\\tank.png");
		mGameObject = new AnonymousEngine::Core::GameObject();
		AnonymousEngine::Graphics::AnimatedSprite* spritesheet = new AnonymousEngine::Graphics::AnimatedSprite(*mGameObject);

		AnonymousEngine::Graphics::Frame* frame1 = new AnonymousEngine::Graphics::Frame;
		frame1->mFilePath = "resources\\General.png";
		frame1->mFrameID = 1;
		frame1->mFrameName = "";
		frame1->mPosition = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		frame1->width = 16;
		frame1->height = 15;

		AnonymousEngine::Graphics::Frame* frame2 = new AnonymousEngine::Graphics::Frame;
		frame2->mFilePath = "resources\\General.png";
		frame2->mFrameID = 1;
		frame2->mFrameName = "";
		frame2->mPosition = glm::vec4(16.0f, 0.0f, 0.0f, 0.0f);
		frame2->width = 16;
		frame2->height = 15;

		spritesheet->SetFrame(*frame1);
		spritesheet->AddFrame(*frame1);
		spritesheet->AddFrame(*frame2);

		spritesheet->SetFPS(24);
	}

	void BattleCity::Init()
	{
		mAudio.Initialize();
		mGameObject->GetSprite().Init("resources\\General.png");
		mWorld = &mLevelManager.LoadWorld();
		mWorld->InitializeWorld();
		mLevelManager.LoadLevelTiles(mWorld->GetWorldState().GetCurrentLevel());
		//mWorld = &mLevelManager.LoadWorld();
		//mWorld->InitializeWorld();
		//mLevelManager.LoadLevelTiles(mWorld->GetWorldState().GetCurrentLevel());

		mGameObject->GetSprite().Init("resources\\General.png");
		mGameObject->SetPosition(glm::vec4(100.0f, 104.0f, 0.0f, 0.0f));

		//mGameObject->GetSprite().SetTint(AnonymousEngine::Graphics::Color::RED);
	}

	void BattleCity::Update()
	{
		mGameClock.UpdateGameTime(mWorld->GetWorldState().mGameTime);
		mWorld->Update();
		//mGameClock.UpdateGameTime(mWorld->GetWorldState().mGameTime);
		//mWorld->Update();

		//mSprite->Render();
		//mSprite->Update(pDeltaTime);
		
		
		float deltaTime = mWorld->GetWorldState().mGameTime.ElapsedGameTime().count() / 1000.0f;

		//GameObject->SetPosition(mGameObject->GetPosition() + glm::vec4(0.0f, -20.0f, 0.0f, 0.0f) * deltaTime);
		//mGameObject->SetRotation(mGameObject->GetRotation() + 90.0f * deltaTime);
		//mGameObject->SetRotation(90.0f);

		mGameObject->GetSprite().Render();
		mGameObject->GetSprite().Update(deltaTime);

		OutputDebugString("BattleCity : Update\n");
	}
}