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
		
		//mSprite = new AnonymousEngine::Graphics::Sprite();
		//ServiceLocator::GetTextureLoader()->GetTexture("resources\\tank.png");
		
		//mGameObject = new AnonymousEngine::Core::GameObject();
		//
		mGameObject = new AnonymousEngine::TankPlayer;

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

		mWorld = new AnonymousEngine::World("World");
		mWorldState.mWorld = mWorld;
	}

	void BattleCity::Init()
	{
		//mWorld = &mLevelManager.LoadWorld();
		//mWorld->InitializeWorld();
		//mLevelManager.LoadLevelTiles(mWorld->GetWorldState().GetCurrentLevel());
		mGameObject->GetSprite().Init("resources\\General.png");

		//
		mInputHandler = new AnonymousEngine::InputHandler();
	}

	void BattleCity::Update()
	{
		//mGameClock.UpdateGameTime(mWorld->GetWorldState().mGameTime);
		//mWorld->Update();

		//mSprite->Render();
		//mSprite->Update(pDeltaTime);
		
		//mGameObject->SetPosition(mGameObject->GetPosition() + glm::vec4(0.0f, -1.0f, 0.0f, 0.0f) * pDeltaTime);

		

		OutputDebugString("BattleCity : Update\n");

		//
		mWorldState;
		mInputHandler->Update(mWorldState);
		mGameObject->Update(mWorldState);
	}
}
