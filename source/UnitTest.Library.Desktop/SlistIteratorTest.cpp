#include "Pch.h"
#include "Foo.h"
#include "SList.h"
#include "SListIteratorTestTemplate.h"
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
			std::uint32_t values[size] = {(*mDistribution)(*mGenerator), (*mDistribution)(*mGenerator), (*mDistribution)(*mGenerator)};
			std::uint32_t* ptrValues[size] = {&values[0], &values[1], &values[2]};
			Foo foos[size] = {Foo(values[0]), Foo(values[1]), Foo(values[2])};
			SListIteratorTestTemplate<std::uint32_t>::TestIteration(values, size);
			SListIteratorTestTemplate<std::uint32_t*>::TestIteration(ptrValues, size);
			SListIteratorTestTemplate<Foo>::TestIteration(foos, size);
		}

		TEST_METHOD(TestCopyConstructor)
		{
			std::uint32_t value = (*mDistribution)(*mGenerator);
			SListIteratorTestTemplate<std::uint32_t>::TestCopyConstructor(value);
			SListIteratorTestTemplate<std::uint32_t*>::TestCopyConstructor(&value);
			SListIteratorTestTemplate<Foo>::TestCopyConstructor(Foo(value));
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			std::uint32_t value = (*mDistribution)(*mGenerator);
			SListIteratorTestTemplate<std::uint32_t>::TestAssignmentOperator(value);
			SListIteratorTestTemplate<std::uint32_t*>::TestAssignmentOperator(&value);
			SListIteratorTestTemplate<Foo>::TestAssignmentOperator(Foo(value));
		}

		TEST_METHOD(TestPostAndPreIncrementOperators)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListIteratorTestTemplate<std::uint32_t>::TestPostAndPreIncrementOperators(value1, value2);
			SListIteratorTestTemplate<std::uint32_t*>::TestPostAndPreIncrementOperators(&value1, &value2);
			SListIteratorTestTemplate<Foo>::TestPostAndPreIncrementOperators(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestIncrementOperatorsThrowsException)
		{
			std::uint32_t value = (*mDistribution)(*mGenerator);
			SListIteratorTestTemplate<std::uint32_t>::TestIncrementOperatorsThrowsException(value);
			SListIteratorTestTemplate<std::uint32_t*>::TestIncrementOperatorsThrowsException(&value);
			SListIteratorTestTemplate<Foo>::TestIncrementOperatorsThrowsException(Foo(value));
		}

		TEST_METHOD(TestDereferenceOperator)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListIteratorTestTemplate<std::uint32_t>::TestDereferenceOperator(value1, value2);
			SListIteratorTestTemplate<std::uint32_t*>::TestDereferenceOperator(&value1, &value2);
			SListIteratorTestTemplate<Foo>::TestDereferenceOperator(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestEqualAndNotEqualOperators)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListIteratorTestTemplate<std::uint32_t>::TestEqualAndNotEqualOperators(value1, value2);
			SListIteratorTestTemplate<std::uint32_t*>::TestEqualAndNotEqualOperators(&value1, &value2);
			SListIteratorTestTemplate<Foo>::TestEqualAndNotEqualOperators(Foo(value1), Foo(value2));
		}

		TEST_CLASS_INITIALIZE(BeginClass)
		{
			std::random_device mDevice;
			mGenerator = new std::default_random_engine(mDevice());
			mDistribution = new std::uniform_int_distribution<std::uint32_t>(0, UINT32_MAX);
		}

		TEST_CLASS_CLEANUP(EndClass)
		{
			delete mGenerator;
			delete mDistribution;
		}

#if _DEBUG
		TEST_METHOD_INITIALIZE(Setup)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&mStartMemState);
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			_CrtMemState endMemState;
			_CrtMemState diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &mStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory leak...");
			}
		}
	private:
		_CrtMemState mStartMemState;
#else
	private:
#endif
		static std::default_random_engine* mGenerator;
		static std::uniform_int_distribution<std::uint32_t>* mDistribution;
	};

	std::default_random_engine* SListIteratorTest::mGenerator;
	std::uniform_int_distribution<std::uint32_t>* SListIteratorTest::mDistribution;
}
