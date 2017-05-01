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

		const string FrameManager::sSpriteSheetAttributeName = "spritesheet";
		const string FrameManager::sFrameIDAttribute = "id";

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
			return const_cast<Frame*>(const_cast<const FrameManager*>(this)->GetFrameEntity(name));
		}

		const Frame* FrameManager::GetFrameEntity(const string& name) const
		{
			Datum* entityDatum = const_cast<Datum*>(Find(name));
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
					Datum* integerIDDatum = frame->Find(sFrameIDAttribute);

					if (integerIDDatum == nullptr)
					{
						throw exception("Frame entity does not have a name attribute.");
					}

					assert(integerIDDatum->Size() == 1);
					mHashmapSpriteID.Insert(make_pair(integerIDDatum->Get<int32_t>(), frame));
				}
			}
		}

		Frame* FrameManager::GetFrameEntity(const int32_t frameID)
		{
			return const_cast<Frame*>(const_cast<const FrameManager*>(this)->GetFrameEntity(frameID));
		}

		const Frame* FrameManager::GetFrameEntity(const std::int32_t frameID) const
		{
			HashMap<int32_t, Frame*>::Iterator hashmapIterator = mHashmapSpriteID.Find(frameID);
			if (hashmapIterator == mHashmapSpriteID.end())
			{
				return nullptr;
			}
			else
			{
				return hashmapIterator->second;
			}
		}
	}
}