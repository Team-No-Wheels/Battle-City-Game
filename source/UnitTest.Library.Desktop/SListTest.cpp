#include "Pch.h"
#include "SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(SListTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			Library::SList<std::uint32_t>* list = new Library::SList<std::uint32_t>();
			Assert::IsNotNull(list);
			Assert::AreEqual(static_cast<std::uint32_t>(0), list->Size());
			delete list;
		}

		TEST_METHOD(TestCopyConstructor)
		{
			Library::SList<std::uint32_t> list1;
			list1.PushFront(0);
			list1.PushFront(rand());
			_CrtMemState memStateBeforeAssignment;
			_CrtMemCheckpoint(&memStateBeforeAssignment);

			// Verify that new memory has been allocated and lists are equivalent
			Library::SList<std::uint32_t> list2(list1);
			Assert::IsTrue(DidMemoryStateChange(memStateBeforeAssignment));
			Assert::AreEqual(list1.Size(), list2.Size());
			Assert::AreEqual(list1.Front(), list2.Front());
			Assert::AreEqual(list1.Back(), list2.Back());
		}

		TEST_METHOD(TestAssignmentOperatorSuccess)
		{
			Library::SList<std::uint32_t> list1;
			Library::SList<std::uint32_t> list2;

			list1.PushFront(rand());
			list1.PushFront(rand());
			_CrtMemState memStateBeforeAssignment;
			_CrtMemCheckpoint(&memStateBeforeAssignment);

			// Verify that new memory has been allocated and lists are equivalent
			list2 = list1;
			Assert::IsTrue(DidMemoryStateChange(memStateBeforeAssignment));
			Assert::AreEqual(list1.Size(), list2.Size());
			Assert::AreEqual(list1.Front(), list2.Front());
			Assert::AreEqual(list1.Back(), list2.Back());
		}

		TEST_METHOD(TestAssignmentOperatorSelfCopyPrevention)
		{
			Library::SList<std::uint32_t> list1;

			list1.PushFront(rand());
			list1.PushFront(rand());
			_CrtMemState memStateBeforeAssignment;
			_CrtMemCheckpoint(&memStateBeforeAssignment);

			// Verify that no new memory has been allocated
			list1 = list1;
			Assert::IsFalse(DidMemoryStateChange(memStateBeforeAssignment));
		}

		TEST_METHOD(TestPushFront)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			std::uint32_t value = rand();
			list.PushFront(rand());
			list.PushFront(value);
			Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
			Assert::AreEqual(value, list.Front());
		}

		TEST_METHOD(TestPopFrontRemovesItemAndUpdatesSize)
		{
			Library::SList<std::uint32_t> list;
			std::uint32_t value = rand();
			list.PushFront(value);
			list.PushFront(rand());
			list.PushBack(rand());
			Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
			list.PopFront();
			Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
			Assert::AreEqual(value, list.Front());
		}

		TEST_METHOD(TestPushBack)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			std::uint32_t value = rand();
			list.PushBack(rand());
			list.PushBack(value);
			Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
			Assert::AreEqual(value, list.Back());
		}

		TEST_METHOD(TestFrontReturnsItemInTheFront)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			list.PushFront(rand());
			std::uint32_t value = rand();
			list.PushFront(value);
			list.PushBack(rand());
			Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
			Assert::AreEqual(value, list.Front());
		}

		TEST_METHOD(TestModifyingFrontValue)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			std::uint32_t value = rand();
			list.PushFront(value);
			Assert::AreEqual(value, list.Front());
			std::uint32_t newValue = rand();
			list.Front() = newValue;
			Assert::AreEqual(newValue, list.Front());
		}

		TEST_METHOD(TestFrontThrowsExceptionWhenListIsEmpty)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			Assert::ExpectException <std::exception>([&list] () { list.Front(); }, L"Front on empty list did not throw an exception");
		}

		TEST_METHOD(TestBackReturnsItemInTheBack)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			std::uint32_t value = rand();
			list.PushBack(rand());
			list.PushBack(value);
			list.PushFront(rand());
			Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
			Assert::AreEqual(value, list.Back());
		}

		TEST_METHOD(TestBackThrowsExceptionWhenListIsEmpty)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			Assert::ExpectException <std::exception>([&list]() { list.Front(); }, L"Back on empty list did not throw an exception");
		}

		TEST_METHOD(TestModifyingBackValue)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			std::uint32_t value = rand();
			list.PushBack(value);
			Assert::AreEqual(value, list.Front());
			std::uint32_t newValue = rand();
			list.Back() = newValue;
			Assert::AreEqual(newValue, list.Back());
		}

		TEST_METHOD(TestSizeMethod)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			list.PushBack(rand());
			Assert::AreEqual(static_cast<std::uint32_t>(1), list.Size());
			list.PushFront(rand());
			Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
			list.PopFront();
			Assert::AreEqual(static_cast<std::uint32_t>(1), list.Size());
			list.PopFront();
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
		}

		TEST_METHOD(TestEmptyMethod)
		{
			Library::SList<std::uint32_t> list;
			Assert::IsTrue(list.IsEmpty());
			list.PushBack(rand());
			Assert::IsFalse(list.IsEmpty());
			list.PopFront();
			Assert::IsTrue(list.IsEmpty());
		}

		TEST_METHOD(TestClear)
		{
			Library::SList<std::uint32_t> list;
			Assert::IsTrue(list.IsEmpty());
			list.PushBack(rand());
			list.PushFront(rand());
			Assert::IsFalse(list.IsEmpty());
			list.Clear();
			Assert::IsTrue(list.IsEmpty());
		}

		TEST_CLASS_INITIALIZE(BeginClass)
		{
			srand(static_cast<unsigned int>(time(nullptr)));
		}

		TEST_METHOD_INITIALIZE(Setup)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&mStartMemState);
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			if (DidMemoryStateChange(mStartMemState))
			{
				Assert::Fail(L"Memory leak...");
			}
		}
	private:
		_CrtMemState mStartMemState;

		static bool DidMemoryStateChange(_CrtMemState startState)
		{
			_CrtMemState endMemState;
			_CrtMemState diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &startState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				return true;
			}
			return false;
		}
	};
}
