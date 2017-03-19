#include "Pch.h"
#include "TestSharedData.h"

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(TestSharedData)

	TestSharedData::TestSharedData() :
		mCurrentYear(0)
	{
	}

	SharedData* TestSharedData::Clone() const
	{
		return new TestSharedData();
	}

	void TestSharedData::SetYear(std::uint32_t year)
	{
		mCurrentYear = year;
	}

	void TestSharedData::AppendCategoryToYear(const std::string& name, const std::string& game)
	{
		mAwardsOverYears[mCurrentYear].PushBack(Category(name, game));
	}
}
