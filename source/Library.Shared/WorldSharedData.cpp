#include "WorldSharedData.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(WorldSharedData)

		WorldSharedData::WorldSharedData() :
			mAttributed(nullptr), mMatrixIndex(0)
		{
		}

		WorldSharedData::~WorldSharedData()
		{
			delete mAttributed;
		}

		SharedData* WorldSharedData::Create() const
		{
			return new WorldSharedData();
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
