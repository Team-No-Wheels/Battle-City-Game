#include "Pch.h"
#include "TestSharedData.h"

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(TestSharedData)

	TestSharedData::TestSharedData()
	{

	}

	SharedData* TestSharedData::Clone()
	{
		return this;
	}
}
