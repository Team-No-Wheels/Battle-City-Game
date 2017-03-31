#include "WorldSharedData.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(WorldSharedData)

		SharedData* WorldSharedData::Clone() const
		{
			WorldSharedData* data = new WorldSharedData();
			data->mDepth = mDepth;
			data->mParser = mParser;
			data->mAttributed = mAttributed;
			return data;
		}

		void WorldSharedData::Initialize()
		{
			SharedData::Initialize();
			mAttributed = nullptr;
		}
	}
}
