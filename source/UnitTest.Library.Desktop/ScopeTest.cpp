#include "Pch.h"
#include "Foo.h"
#include "Scope.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ScopeTest)
	{
	public:
		typedef AnonymousEngine::Datum Datum;
		typedef Datum::DatumType DatumType;
		typedef AnonymousEngine::Scope Scope;

		TEST_METHOD(TestDefaultConstructor)
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
	private:

		static TestClassHelper mHelper;
	};

	TestClassHelper ScopeTest::mHelper;
}
