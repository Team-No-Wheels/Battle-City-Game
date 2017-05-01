#include "Pch.h"
#include "FrameManager.h"

using namespace std;

namespace AnonymousEngine
{
	namespace Graphics
	{
		ATTRIBUTED_DEFINITIONS(FrameManager)
		ENTITY_FACTORY_DEFINITIONS(FrameManager)

		const string FrameManager::sSpriteSheetAttributeName = "SpriteSheet";

		FrameManager::FrameManager()
			:mSpriteSheetName(), mHashmapSpriteID(100)
		{
			AddExternalAttribute(sSpriteSheetAttributeName, &mSpriteSheetName, 1);
		}

		void FrameManager::AppendPrescribedAttributeNames(AnonymousEngine::Vector<string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack(sSpriteSheetAttributeName);
		}

		Frame* FrameManager::GetFrameEntity(const string& name)
		{
			Datum* entityDatum = Find(name);
			if (entityDatum == nullptr)
			{
				return nullptr;
			}
			assert(entityDatum->Size() == 1);
			assert(entityDatum->Get<Scope>(0).Is("Frame"));

			return &(static_cast<Frame&>(entityDatum->Get<Scope>(0)));
		}			
	}
}