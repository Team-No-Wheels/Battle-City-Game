#include "WorldSharedData.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(WorldSharedData)

		WorldSharedData::WorldSharedData() :
			mWorld(nullptr)
		{
		}

		SharedData* WorldSharedData::Clone() const
		{
			WorldSharedData* data = new WorldSharedData();
			data->mDepth = mDepth;
			data->mParser = mParser;
			data->mWorld = (mWorld == nullptr) ? nullptr : new Containers::World(mWorld->Name());
			return data;
		}

		void WorldSharedData::Initialize()
		{
			SharedData::Initialize();
			mWorld = nullptr;
		}
	}
}
