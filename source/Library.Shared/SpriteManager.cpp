#include "Pch.h"
#include "SpriteManager.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		ATTRIBUTED_DEFINITIONS(SpriteManager)
		ENTITY_FACTORY_DEFINITIONS(SpriteManager)

		const std::string SpriteManager::sSpriteSheetAttributeName = "SpriteSheetName";

		SpriteManager::SpriteManager()
			:mSpriteSheetName()
		{
			AddExternalAttribute(sSpriteSheetAttributeName, &mSpriteSheetName, 1);
		}

		void SpriteManager::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack(sSpriteSheetAttributeName);
		}
	}
}