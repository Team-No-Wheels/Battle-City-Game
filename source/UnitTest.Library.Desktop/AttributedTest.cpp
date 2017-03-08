#include "Pch.h"
#include "Attributed.h"
#include "AttributedFoo.h"
#include "AttributedBar.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(AttributedTest)
	{
		typedef AnonymousEngine::Attributed Attributed;
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			Attributed attributed;
			AttributedFoo foo;
			AttributedFoo bar;
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
	private:

		static TestClassHelper mHelper;
	};

	TestClassHelper AttributedTest::mHelper;
}
