#include "Pch.h"
#include "Renderable.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		ATTRIBUTED_DEFINITIONS(Renderable)
		
		Renderable::Renderable() :
			mAlpha(1.0f), mTextureID(0)
		{
			AddExternalAttribute("Alpha", &mAlpha, 1);
			AddExternalAttribute("Width", &mWidth, 1);
			AddExternalAttribute("Height", &mHeight, 1);
			AddExternalAttribute("Position", &mPosition, 1);
		}

		void Renderable::Init(const std::string& pFilePath)
		{
			pFilePath;
		}

		void Renderable::Update(float pDeltaTime)
		{
			pDeltaTime;
		}

		void Renderable::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Alpha");
			prescribedAttributeNames.PushBack("Width");
			prescribedAttributeNames.PushBack("Height");
			prescribedAttributeNames.PushBack("Position");
		}
	}	
}