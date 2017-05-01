#include "Pch.h"
#include "Renderable.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		Renderable::Renderable() :
			mAlpha(1.0f), mTexture(nullptr), isInitialized(false)
		{
		}

		void Renderable::Init(const std::string& pFilePath)
		{
			pFilePath;
			isInitialized = true;
		}

		void Renderable::Update(float pDeltaTime)
		{
			pDeltaTime;
		}

	}	
}