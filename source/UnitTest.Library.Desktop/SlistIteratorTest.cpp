#include "Pch.h"
#include "Foo.h"
#include "SListIteratorTestTemplate.h"
#include "TestClassHelper.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(SListIteratorTest)
	{
	public:
		TEST_METHOD(TestIteration)
		{
			const std::uint32_t size = 3;
			std::uint32_t values[size] = {mHelper.GetRandomUInt32(), mHelper.GetRandomUInt32(), mHelper.GetRandomUInt32()};
			std::uint32_t* ptrValues[size] = {&values[0], &values[1], &values[2]};
			Foo foos[size] = {Foo(values[0]), Foo(values[1]), Foo(values[2])};
			SListIteratorTestTemplate<std::uint32_t>::TestIteration(values, size);
			SListIteratorTestTemplate<std::uint32_t*>::TestIteration(ptrValues, size);
			SListIteratorTestTemplate<Foo>::TestIteration(foos, size);
		}

		TEST_METHOD(TestCopyConstructor)
		{
			std::uint32_t value = mHelper.GetRandomUInt32();
			SListIteratorTestTemplate<std::uint32_t>::TestCopyConstructor(value);
			SListIteratorTestTemplate<std::uint32_t*>::TestCopyConstructor(&value);
			SListIteratorTestTemplate<Foo>::TestCopyConstructor(Foo(value));
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			std::uint32_t value = mHelper.GetRandomUInt32();
			SListIteratorTestTemplate<std::uint32_t>::TestAssignmentOperator(value);
			SListIteratorTestTemplate<std::uint32_t*>::TestAssignmentOperator(&value);
			SListIteratorTestTemplate<Foo>::TestAssignmentOperator(Foo(value));
		}

		TEST_METHOD(TestPostAndPreIncrementOperators)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			SListIteratorTestTemplate<std::uint32_t>::TestPostAndPreIncrementOperators(value1, value2);
			SListIteratorTestTemplate<std::uint32_t*>::TestPostAndPreIncrementOperators(&value1, &value2);
			SListIteratorTestTemplate<Foo>::TestPostAndPreIncrementOperators(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestIncrementOperatorsThrowsException)
		{
			std::uint32_t value = mHelper.GetRandomUInt32();
			SListIteratorTestTemplate<std::uint32_t>::TestIncrementOperatorsThrowsException(value);
			SListIteratorTestTemplate<std::uint32_t*>::TestIncrementOperatorsThrowsException(&value);
			SListIteratorTestTemplate<Foo>::TestIncrementOperatorsThrowsException(Foo(value));
		}

		TEST_METHOD(TestDereferenceOperator)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			SListIteratorTestTemplate<std::uint32_t>::TestDereferenceOperator(value1, value2);
			SListIteratorTestTemplate<std::uint32_t*>::TestDereferenceOperator(&value1, &value2);
			SListIteratorTestTemplate<Foo>::TestDereferenceOperator(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestEqualAndNotEqualOperators)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			SListIteratorTestTemplate<std::uint32_t>::TestEqualAndNotEqualOperators(value1, value2);
			SListIteratorTestTemplate<std::uint32_t*>::TestEqualAndNotEqualOperators(&value1, &value2);
			SListIteratorTestTemplate<Foo>::TestEqualAndNotEqualOperators(Foo(value1), Foo(value2));
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

	TestClassHelper SListIteratorTest::mHelper;
}
