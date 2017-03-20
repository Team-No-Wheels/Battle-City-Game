#include "Pch.h"
#include "TestSharedData.h"

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(TestSharedData)

	TestSharedData::TestSharedData() :
		mAwardWinners(nullptr)
	{
	}

	TestSharedData::~TestSharedData()
	{
		delete mAwardWinners;
	}

	SharedData* TestSharedData::Clone() const
	{
		return new TestSharedData();
	}

	AnonymousEngine::Scope*& TestSharedData::AwardWinners()
	{
		return mAwardWinners;
	}
}
