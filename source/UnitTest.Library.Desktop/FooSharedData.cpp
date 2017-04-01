#include "Pch.h"
#include "FooSharedData.h"

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(FooSharedData)

	FooSharedData::FooSharedData() :
		mAwardWinners(nullptr)
	{
	}

	SharedData* FooSharedData::Create() const
	{
		FooSharedData* data = new FooSharedData();
		data->mDepth = mDepth;
		data->mParser = mParser;
		data->mAwardWinners = (mAwardWinners == nullptr) ? nullptr : new AnonymousEngine::Scope(*mAwardWinners);
		return data;
	}

	void FooSharedData::Initialize()
	{
		SharedData::Initialize();
		delete mAwardWinners;
		mAwardWinners = nullptr;
	}
}
