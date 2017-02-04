#include "Pch.h"
#include "HashMapTestTemplate.h"
#include "TestClassHelper.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(HashMapTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			HashMapTestTemplate<std::uint32_t>::TestDefaultConstructor();
			HashMapTestTemplate<std::uint32_t*>::TestDefaultConstructor();
			HashMapTestTemplate<const char*>::TestDefaultConstructor();
			HashMapTestTemplate<char*>::TestDefaultConstructor();
			HashMapTestTemplate<std::string>::TestDefaultConstructor();
			HashMapTestTemplate<const std::string>::TestDefaultConstructor();
			HashMapTestTemplate<Foo>::TestDefaultConstructor();
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

	TestClassHelper HashMapTest::mHelper;
}
