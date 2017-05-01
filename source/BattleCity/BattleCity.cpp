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
		
	}

	void BattleCity::Init()
	{
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
		
		//mGameObject->SetPosition(mGameObject->GetPosition() + glm::vec4(0.0f, -1.0f, 0.0f, 0.0f) * (1.0f/60.0f));
		//mGameObject->SetRotation(mGameObject->GetRotation() + 90.0f * (1.0f / 1000.0f));
		//mGameObject->SetRotation(90.0f);
		mGameObject->GetSprite().Render();
		mGameObject->GetSprite().Update(1.0f / 60.0f);

		OutputDebugString("BattleCity : Update\n");
	}
}
