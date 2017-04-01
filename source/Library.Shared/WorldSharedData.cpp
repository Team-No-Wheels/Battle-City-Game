#include "WorldSharedData.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(WorldSharedData)

		WorldSharedData::WorldSharedData() :
			mAttributed(nullptr)
		{
		}

		WorldSharedData::~WorldSharedData()
		{
			delete mAttributed;
		}

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
			delete mAttributed;
		}

		Containers::World* WorldSharedData::ExtractWorld()
		{
			assert(mAttributed->Is(Containers::World::TypeIdClass()));
			Containers::World* world = static_cast<Containers::World*>(mAttributed);
			mAttributed = nullptr;
			return world;
		}
	}
}
