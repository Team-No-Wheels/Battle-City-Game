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
		//ServiceLocator::GetTextureLoader()->GetTexture("resources\\tank.png");
		mGameObject = new AnonymousEngine::Core::GameObject();
		mGameObject->SetPosition(glm::vec4(100.0f, 100.0f, 0.0f, 0.0f));
	}

	void BattleCity::Init()
	{
		//mSprite->Init("resources\\tank.png");
		mGameObject->GetSprite().Init("resources\\tank.png");
	}

	void BattleCity::Update(float pDeltaTime)
	{
		pDeltaTime;
		//mWorld->Update();

		//mSprite->Render();
		//mSprite->Update(pDeltaTime);
		
		mGameObject->GetSprite().Render();
		mGameObject->GetSprite().Update(pDeltaTime);
		
		OutputDebugString("BattleCity : Update\n");
	}
}
