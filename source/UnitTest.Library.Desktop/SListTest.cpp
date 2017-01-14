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
			delete list;
		}

		TEST_METHOD(TestCopyConstructor)
		{
			Library::SList<std::uint32_t> list1;
			list1.PushFront(rand());
			list1.PushFront(rand());
			_CrtMemState memStateBeforeAssignment;
			_CrtMemCheckpoint(&memStateBeforeAssignment);

			Library::SList<std::uint32_t> list2(list1);
			Assert::IsTrue(DidMemoryStateChange(memStateBeforeAssignment));
			Assert::IsTrue(list1.Size() == list2.Size());
		}

		TEST_METHOD(TestAssignmentOperatorSuccess)
		{
			Library::SList<std::uint32_t> list1;
			Library::SList<std::uint32_t> list2;

			list1.PushFront(rand());
			list1.PushFront(rand());
			_CrtMemState memStateBeforeAssignment;
			_CrtMemCheckpoint(&memStateBeforeAssignment);

			list2 = list1;
			Assert::IsTrue(DidMemoryStateChange(memStateBeforeAssignment));
			Assert::IsTrue(list1.Size() == list2.Size());
		}

		TEST_METHOD(TestAssignmentOperatorSelfCopyPrevention)
		{
			Library::SList<std::uint32_t> list1;

			list1.PushFront(rand());
			list1.PushFront(rand());
			_CrtMemState memStateBeforeAssignment;
			_CrtMemCheckpoint(&memStateBeforeAssignment);

			list1 = list1;
			Assert::IsFalse(DidMemoryStateChange(memStateBeforeAssignment));
		}

		TEST_METHOD(TestPushFront)
		{
			Library::SList<std::uint32_t> list;
			Assert::IsTrue(list.Size() == 0);
			list.PushFront(rand());
			Assert::IsTrue(list.Size() == 1);
		}

		TEST_METHOD(TestPopFrontReturnsCorrectValueAndUpdatesSize)
		{
			Library::SList<std::uint32_t> list;
			std::uint32_t value = rand();
			list.PushFront(rand());
			list.PushFront(value);
			list.PushBack(rand());
			Assert::IsTrue(list.Size() == 3);
			Assert::IsTrue(list.PopFront() == value);
		}

		TEST_METHOD(TestPopFrontOnEmptyListThrowsException)
		{
			Library::SList<std::uint32_t> list;
			bool didThrowException = false;
			try
			{
				list.PopFront();
			}
			catch (std::exception)
			{
				didThrowException = true;
			}

			if (!didThrowException)
			{
				Assert::Fail(L"PopFront on empty list did not throw an exception");
			}
		}

		TEST_METHOD(TestPushBack)
		{
			Library::SList<std::uint32_t> list;
			Assert::IsTrue(list.Size() == 0);
			list.PushBack(rand());
			Assert::IsTrue(list.Size() == 1);
		}

		TEST_METHOD(TestFrontReturnsItemInTheFront)
		{
			Library::SList<std::uint32_t> list;
			Assert::IsTrue(list.Size() == 0);
			list.PushFront(rand());
			std::uint32_t value = rand();
			list.PushFront(value);
			list.PushBack(rand());
			Assert::IsTrue(list.Size() == 3);
			Assert::IsTrue(list.Front() == value);
		}

		TEST_METHOD(TestFrontThrowsExceptionWhenListIsEmpty)
		{
			Library::SList<std::uint32_t> list;
			Assert::IsTrue(list.Size() == 0);
			bool didThrowException = false;
			try
			{
				list.Front();
			}
			catch(std::exception)
			{
				didThrowException = true;
			}

			if (!didThrowException)
			{
				Assert::Fail(L"Front on empty list did not throw an exception");
			}
		}

		TEST_METHOD(TestBackReturnsItemInTheBack)
		{
			Library::SList<std::uint32_t> list;
			Assert::IsTrue(list.Size() == 0);
			std::uint32_t value = rand();
			list.PushBack(rand());
			list.PushBack(value);
			list.PushFront(rand());
			Assert::IsTrue(list.Size() == 3);
			Assert::IsTrue(list.Back() == value);
		}

		TEST_METHOD(TestBackThrowsExceptionWhenListIsEmpty)
		{
			Library::SList<std::uint32_t> list;
			Assert::IsTrue(list.Size() == 0);
			bool didThrowException = false;
			try
			{
				list.Back();
			}
			catch (std::exception)
			{
				didThrowException = true;
			}

			if (!didThrowException)
			{
				Assert::Fail(L"Back on empty list did not throw an exception");
			}
		}

		TEST_METHOD(TestSizeMethod)
		{
			Library::SList<std::uint32_t> list;
			Assert::IsTrue(list.Size() == 0);
			list.PushBack(rand());
			Assert::IsTrue(list.Size() == 1);
			list.PushFront(rand());
			Assert::IsTrue(list.Size() == 2);
			list.PopFront();
			Assert::IsTrue(list.Size() == 1);
			list.PopFront();
			Assert::IsTrue(list.Size() == 0);
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

		TEST_METHOD(TestBasicFunctionalityWithStringObjects)
		{
			Library::SList<std::string> list;
			Assert::IsTrue(list.IsEmpty());
			Assert::IsTrue(list.Size() == 0);
			list.PushBack("XYZ999");
			list.PushFront("ABCD1234");
			list.PushFront("EFGH5678");
			Assert::IsTrue(list.Size() == 3);
			Assert::IsTrue(list.PopFront() == "EFGH5678");
			Assert::IsTrue(list.Size() == 2);
			Assert::IsTrue(list.Front() == "ABCD1234");
			Assert::IsTrue(list.Back() == "XYZ999");
			list.Clear();
			Assert::IsTrue(list.Size() == 0);
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
