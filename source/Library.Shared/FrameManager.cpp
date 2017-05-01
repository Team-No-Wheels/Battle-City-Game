#include "Pch.h"
#include "FrameManager.h"
#include "Datum.h"

using namespace std;

namespace AnonymousEngine
{
	namespace Graphics
	{
		ATTRIBUTED_DEFINITIONS(FrameManager)
		ENTITY_FACTORY_DEFINITIONS(FrameManager)

		const string FrameManager::sSpriteSheetAttributeName = "SpriteSheet";
		const string FrameManager::sFrameIDAttributeName = "name";

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

		void FrameManager::StoreAllFrames()
		{
			for (pair<const string, Datum>* stringDatumPair : mOrderVector)
			{
				Datum& datum = stringDatumPair->second;
				if (datum.Type() == Datum::DatumType::Scope && datum.Get<Scope>().Is(Frame::TypeIdClass()))
				{
					assert(datum.Size() == 1);
					Frame* frame = &static_cast<Frame&>(datum.Get<Scope>());
					Datum* integerIDDatum = frame->Find(sFrameIDAttributeName);

					if (integerIDDatum == nullptr)
					{
						
					}
				}
			}
		}
	}
}