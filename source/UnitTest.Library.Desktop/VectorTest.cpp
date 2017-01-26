#include "Pch.h"
#include "Foo.h"
#include "VectorTestTemplate.h"
#include "TestClassHelper.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(VectorTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			VectorTestTemplate<std::uint32_t>::TestDefaultConstructor();
			VectorTestTemplate<std::uint32_t*>::TestDefaultConstructor();
			VectorTestTemplate<Foo>::TestDefaultConstructor();
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

	TestClassHelper VectorTest::mHelper;
}
