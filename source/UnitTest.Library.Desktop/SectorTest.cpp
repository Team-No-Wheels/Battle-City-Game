#include "Pch.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestLibraryDesktop
{
	using namespace AnonymousEngine;

	TEST_CLASS(SectorTest)
	{
	public:
		TEST_METHOD(TestInitialize)
		{

		}
		TEST_CLASS_INITIALIZE(InitializeClass)
		{
			mHelper.BeginClass();
		}

		TEST_METHOD_INITIALIZE(Setup)
		{
			mHelper.Setup();
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			mHelper.Teardown();
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			mHelper.EndClass();
		}

		static TestClassHelper mHelper;
	};

	TestClassHelper SectorTest::mHelper;
}
