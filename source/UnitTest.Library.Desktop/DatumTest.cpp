#include "Pch.h"
#include "Foo.h"
#include "DatumTestTemplate.h"
#include "TestClassHelper.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(DatumTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			DatumTestTemplate<std::uint32_t>::TestDefaultConstructor();
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

	TestClassHelper DatumTest::mHelper;
}
