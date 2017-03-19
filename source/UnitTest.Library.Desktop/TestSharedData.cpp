#include "Pch.h"
#include "TestSharedData.h"

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(TestSharedData)

	SharedData* TestSharedData::Clone() const
	{
		return new TestSharedData();
	}

	std::string& TestSharedData::CurrentElementName()
	{
		return mCurrentElementName;
	}

	AnonymousEngine::Scope& TestSharedData::AwardWinners()
	{
		return *mAwardWinners;
	}

	AnonymousEngine::Vector<AnonymousEngine::Scope*>& TestSharedData::GetStack()
	{
		return mStack;
	}
}
