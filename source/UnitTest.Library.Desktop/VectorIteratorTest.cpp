#include "Pch.h"
#include "Foo.h"
#include "VectorIteratorTestTemplate.h"
#include "TestClassHelper.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(VectorIteratorTest)
	{
	public:
		TEST_METHOD(TestDerefenceOperator)
		{
			std::uint32_t value = mHelper.GetRandomUInt32();
			VectorIteratorTestTemplate<std::uint32_t>::TestDerefenceOperator(value);
			VectorIteratorTestTemplate<std::uint32_t*>::TestDerefenceOperator(&value);
			VectorIteratorTestTemplate<Foo>::TestDerefenceOperator(Foo(value));
		}

		TEST_METHOD(TestPreIncrementOperator)
		{
			std::uint32_t value = mHelper.GetRandomUInt32();
			VectorIteratorTestTemplate<std::uint32_t>::TestPreIncrementOperator(value);
			VectorIteratorTestTemplate<std::uint32_t*>::TestPreIncrementOperator(&value);
			VectorIteratorTestTemplate<Foo>::TestPreIncrementOperator(Foo(value));
		}

		TEST_METHOD(TestPostIncrementOperator)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			VectorIteratorTestTemplate<std::uint32_t>::TestPostIncrementOperator(value1, value2);
			VectorIteratorTestTemplate<std::uint32_t*>::TestPostIncrementOperator(&value1, &value2);
			VectorIteratorTestTemplate<Foo>::TestPostIncrementOperator(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestEqualityOperators)
		{
			std::uint32_t value = mHelper.GetRandomUInt32();
			VectorIteratorTestTemplate<std::uint32_t>::TestEqualityOperators(value);
			VectorIteratorTestTemplate<std::uint32_t*>::TestEqualityOperators(&value);
			VectorIteratorTestTemplate<Foo>::TestEqualityOperators(Foo(value));
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

	TestClassHelper VectorIteratorTest::mHelper;
}
