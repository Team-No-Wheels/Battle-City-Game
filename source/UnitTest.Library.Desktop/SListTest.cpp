#include "Pch.h"
#include "SList.h"
#include "Foo.h"
#include "ToStringTemplates.h"
#include "SListTestTemplate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(SListTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			SListTestTemplate<std::uint32_t>::TestDefaultConstructor();
		}

		TEST_METHOD(TestCopyConstructor)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestCopyConstructor(value1, value2);
			SListTestTemplate<std::uint32_t*>::TestCopyConstructor(&value1, &value2);
			SListTestTemplate<Foo>::TestCopyConstructor(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestAssignmentOperatorSuccess)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestAssignmentOperatorSuccess(value1, value2);
			SListTestTemplate<std::uint32_t*>::TestAssignmentOperatorSuccess(&value1, &value2);
			SListTestTemplate<Foo>::TestAssignmentOperatorSuccess(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestAssignmentOperatorSelfCopyPrevention)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestAssignmentOperatorSelfCopyPrevention(value1, value2);
			SListTestTemplate<std::uint32_t*>::TestAssignmentOperatorSelfCopyPrevention(&value1, &value2);
			SListTestTemplate<Foo>::TestAssignmentOperatorSelfCopyPrevention(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestPushFront)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestPushFront(value1, value2);
			SListTestTemplate<std::uint32_t*>::TestPushFront(&value1, &value2);
			SListTestTemplate<Foo>::TestPushFront(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestPopFrontRemovesItemAndUpdatesSize)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			std::uint32_t value3 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestPopFrontRemovesItemAndUpdatesSize(value1, value2, value3);
			SListTestTemplate<std::uint32_t*>::TestPopFrontRemovesItemAndUpdatesSize(&value1, &value2, &value3);
			SListTestTemplate<Foo>::TestPopFrontRemovesItemAndUpdatesSize(Foo(value1), Foo(value2), Foo(value3));
		}

		TEST_METHOD(TestPushBack)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestPushBack(value1, value2);
			SListTestTemplate<std::uint32_t*>::TestPushBack(&value1, &value2);
			SListTestTemplate<Foo>::TestPushBack(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestFrontReturnsItemInTheFront)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			std::uint32_t value3 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestFrontReturnsItemInTheFront(value1, value2, value3);
			SListTestTemplate<std::uint32_t*>::TestFrontReturnsItemInTheFront(&value1, &value2, &value3);
			SListTestTemplate<Foo>::TestFrontReturnsItemInTheFront(Foo(value1), Foo(value2), Foo(value3));
		}

		TEST_METHOD(TestModifyingFrontValue)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestModifyingFrontValue(value1, value2);
			SListTestTemplate<std::uint32_t*>::TestModifyingFrontValue(&value1, &value2);
			SListTestTemplate<Foo>::TestModifyingFrontValue(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestFrontThrowsExceptionWhenListIsEmpty)
		{
			SListTestTemplate<std::uint32_t>::TestFrontThrowsExceptionWhenListIsEmpty();
			SListTestTemplate<std::uint32_t*>::TestFrontThrowsExceptionWhenListIsEmpty();
			SListTestTemplate<Foo>::TestFrontThrowsExceptionWhenListIsEmpty();
		}

		TEST_METHOD(TestBackReturnsItemInTheBack)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			std::uint32_t value3 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestBackReturnsItemInTheBack(value1, value2, value3);
			SListTestTemplate<std::uint32_t*>::TestBackReturnsItemInTheBack(&value1, &value2, &value3);
			SListTestTemplate<Foo>::TestBackReturnsItemInTheBack(Foo(value1), Foo(value2), Foo(value3));
		}

		TEST_METHOD(TestBackThrowsExceptionWhenListIsEmpty)
		{
			SListTestTemplate<std::uint32_t>::TestBackThrowsExceptionWhenListIsEmpty();
			SListTestTemplate<std::uint32_t*>::TestBackThrowsExceptionWhenListIsEmpty();
			SListTestTemplate<Foo>::TestBackThrowsExceptionWhenListIsEmpty();
		}

		TEST_METHOD(TestModifyingBackValue)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestModifyingBackValue(value1, value2);
			SListTestTemplate<std::uint32_t*>::TestModifyingBackValue(&value1, &value2);
			SListTestTemplate<Foo>::TestModifyingBackValue(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestSizeMethod)
		{
			std::uint32_t value = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestSizeMethod(value);
			SListTestTemplate<std::uint32_t*>::TestSizeMethod(&value);
			SListTestTemplate<Foo>::TestSizeMethod(Foo(value));
		}

		TEST_METHOD(TestEmptyMethod)
		{
			std::uint32_t value = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestEmptyMethod(value);
			SListTestTemplate<std::uint32_t*>::TestEmptyMethod(&value);
			SListTestTemplate<Foo>::TestEmptyMethod(Foo(value));
		}

		TEST_METHOD(TestClear)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestClear(value1, value2);
			SListTestTemplate<std::uint32_t*>::TestClear(&value1, &value2);
			SListTestTemplate<Foo>::TestClear(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestBeginAndEnd)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestBeginAndEnd(value1, value2);
			SListTestTemplate<std::uint32_t*>::TestBeginAndEnd(&value1, &value2);
			SListTestTemplate<Foo>::TestBeginAndEnd(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestFind)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			std::uint32_t value3 = (*mDistribution)(*mGenerator);
			std::uint32_t value4 = (*mDistribution)(*mGenerator);
			std::uint32_t value5 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestFind(value1, value2, value3, value4, value5);
			SListTestTemplate<std::uint32_t*>::TestFind(&value1, &value2, &value3, &value4, &value5);
			SListTestTemplate<Foo>::TestFind(Foo(value1), Foo(value2), Foo(value3), Foo(value4), Foo(value5));
		}

		TEST_METHOD(TestInsertAfter)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			std::uint32_t value3 = (*mDistribution)(*mGenerator);
			std::uint32_t value4 = (*mDistribution)(*mGenerator);
			std::uint32_t value5 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestInsertAfter(value1, value2, value3, value4, value5);
			SListTestTemplate<std::uint32_t*>::TestInsertAfter(&value1, &value2, &value3, &value4, &value5);
			SListTestTemplate<Foo>::TestInsertAfter(Foo(value1), Foo(value2), Foo(value3), Foo(value4), Foo(value5));
		}

		TEST_METHOD(TestRemove)
		{
			std::uint32_t value1 = (*mDistribution)(*mGenerator);
			std::uint32_t value2 = (*mDistribution)(*mGenerator);
			std::uint32_t value3 = (*mDistribution)(*mGenerator);
			std::uint32_t value4 = (*mDistribution)(*mGenerator);
			SListTestTemplate<std::uint32_t>::TestRemove(value1, value2, value3, value4);
			SListTestTemplate<std::uint32_t*>::TestRemove(&value1, &value2, &value3, &value4);
			SListTestTemplate<Foo>::TestRemove(Foo(value1), Foo(value2), Foo(value3), Foo(value4));
			Foo temp;
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

	std::default_random_engine* SListTest::mGenerator;
	std::uniform_int_distribution<std::uint32_t>* SListTest::mDistribution;
}
