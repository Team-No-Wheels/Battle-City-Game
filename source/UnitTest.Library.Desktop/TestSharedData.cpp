#include "Pch.h"
#include "TestSharedData.h"

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(TestSharedData)

	TestSharedData::TestSharedData() :
		mAwardWinners(new AnonymousEngine::Scope())
	{
	}

	TestSharedData::~TestSharedData()
	{
		delete mAwardWinners;
	}

	SharedData* TestSharedData::Clone() const
	{
		TestSharedData* data = new TestSharedData();
		data->mDepth = mDepth;
		data->mParser = mParser;
		*(data->mAwardWinners) = *mAwardWinners;
		return data;
	}

	void TestSharedData::Initialize()
	{
	}

	AnonymousEngine::Scope*& TestSharedData::AwardWinners()
	{
		return mAwardWinners;
	}
}
