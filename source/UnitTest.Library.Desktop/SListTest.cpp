#include "Pch.h"
#include "SList.h"
#include "Foo.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(SListTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			// test for primitive type
			Library::SList<std::uint32_t>* list1 = new Library::SList<std::uint32_t>();
			Assert::IsNotNull(list1);
			Assert::AreEqual(static_cast<std::uint32_t>(0), list1->Size());
			delete list1;

			// test for pointer type
			Library::SList<std::uint32_t*>* list2 = new Library::SList<std::uint32_t*>();
			Assert::IsNotNull(list2);
			Assert::AreEqual(static_cast<std::uint32_t>(0), list2->Size());
			delete list2;

			// test for user defined type
			Library::SList<Foo>* list3 = new Library::SList<Foo>();
			Assert::IsNotNull(list3);
			Assert::AreEqual(static_cast<std::uint32_t>(0), list3->Size());
			delete list3;
		}

		TEST_METHOD(TestCopyConstructor)
		{
			{
				// test for primitive type
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

			{
				// test for pointer type
				Library::SList<std::uint32_t*> list1;
				std::uint32_t* value1 = new std::uint32_t(0);
				std::uint32_t* value2 = new std::uint32_t(rand());
				list1.PushFront(value1);
				list1.PushFront(value2);
				_CrtMemState memStateBeforeAssignment;
				_CrtMemCheckpoint(&memStateBeforeAssignment);

				// Verify that new memory has been allocated and lists are equivalent
				Library::SList<std::uint32_t*> list2(list1);
				Assert::IsTrue(DidMemoryStateChange(memStateBeforeAssignment));
				Assert::AreEqual(list1.Size(), list2.Size());
				Assert::AreEqual(list1.Front(), list2.Front());
				Assert::AreEqual(list1.Back(), list2.Back());
				delete value1;
				delete value2;
			}

			{
				// test for user defined type
				Library::SList<Foo> list1;
				list1.PushFront(Foo(0));
				list1.PushFront(Foo(rand()));
				_CrtMemState memStateBeforeAssignment;
				_CrtMemCheckpoint(&memStateBeforeAssignment);

				// Verify that new memory has been allocated and lists are equivalent
				Library::SList<Foo> list2(list1);
				Assert::IsTrue(DidMemoryStateChange(memStateBeforeAssignment));
				Assert::AreEqual(list1.Size(), list2.Size());
				Assert::AreEqual(list1.Front(), list2.Front());
				Assert::AreEqual(list1.Back(), list2.Back());
			}
		}

		TEST_METHOD(TestAssignmentOperatorSuccess)
		{
			// test for primitive 
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

			// test for pointer
			{
				Library::SList<std::uint32_t*> list1;
				Library::SList<std::uint32_t*> list2;

				std::uint32_t* value1 = new std::uint32_t(rand());
				std::uint32_t* value2 = new std::uint32_t(rand());
				list1.PushFront(value1);
				list1.PushFront(value2);
				_CrtMemState memStateBeforeAssignment;
				_CrtMemCheckpoint(&memStateBeforeAssignment);

				// Verify that new memory has been allocated and lists are equivalent
				list2 = list1;
				Assert::IsTrue(DidMemoryStateChange(memStateBeforeAssignment));
				Assert::AreEqual(list1.Size(), list2.Size());
				Assert::AreEqual(list1.Front(), list2.Front());
				Assert::AreEqual(list1.Back(), list2.Back());
				delete value1;
				delete value2;
			}

			// test for user defined type 
			{
				Library::SList<Foo> list1;
				Library::SList<Foo> list2;

				list1.PushFront(Foo(rand()));
				list1.PushFront(Foo(rand()));
				_CrtMemState memStateBeforeAssignment;
				_CrtMemCheckpoint(&memStateBeforeAssignment);

				// Verify that new memory has been allocated and lists are equivalent
				list2 = list1;
				Assert::IsTrue(DidMemoryStateChange(memStateBeforeAssignment));
				Assert::AreEqual(list1.Size(), list2.Size());
				Assert::AreEqual(list1.Front(), list2.Front());
				Assert::AreEqual(list1.Back(), list2.Back());
			}
		}

		TEST_METHOD(TestAssignmentOperatorSelfCopyPrevention)
		{
			// primtive test
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

			// pointer test
			{
				Library::SList<std::uint32_t*> list1;
				std::uint32_t* value1 = new std::uint32_t(rand());
				std::uint32_t* value2 = new std::uint32_t(rand());
				list1.PushFront(value1);
				list1.PushFront(value2);
				_CrtMemState memStateBeforeAssignment;
				_CrtMemCheckpoint(&memStateBeforeAssignment);

				// Verify that no new memory has been allocated
				list1 = list1;
				Assert::IsFalse(DidMemoryStateChange(memStateBeforeAssignment));
				delete value1;
				delete value2;
			}

			// user defined type test
			{
				Library::SList<Foo> list1;

				list1.PushFront(Foo(rand()));
				list1.PushFront(Foo(rand()));
				_CrtMemState memStateBeforeAssignment;
				_CrtMemCheckpoint(&memStateBeforeAssignment);

				// Verify that no new memory has been allocated
				list1 = list1;
				Assert::IsFalse(DidMemoryStateChange(memStateBeforeAssignment));
			}
		}

		TEST_METHOD(TestPushFront)
		{
			// primitive type
			{
				Library::SList<std::uint32_t> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = rand();
				list.PushFront(rand());
				list.PushFront(value);
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(value, list.Front());
			}

			// pointer test
			{
				Library::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value1 = new std::uint32_t(rand());
				std::uint32_t* value2 = new std::uint32_t(rand());
				list.PushFront(value1);
				list.PushFront(value2);
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(value2, list.Front());
				delete value1;
				delete value2;
			}

			// user defined type test
			{
				Library::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = rand();
				list.PushFront(Foo(rand()));
				list.PushFront(Foo(value));
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(Foo(value), list.Front());
			}
		}

		TEST_METHOD(TestPopFrontRemovesItemAndUpdatesSize)
		{
			// primitive test
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

			// pointer test
			{
				Library::SList<std::uint32_t*> list;
				std::uint32_t* value1 = new std::uint32_t(rand());
				std::uint32_t* value2 = new std::uint32_t(rand());
				std::uint32_t* value3 = new std::uint32_t(rand());
				list.PushFront(value1);
				list.PushFront(value2);
				list.PushBack(value3);
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				list.PopFront();
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(value1, list.Front());
				delete value1;
				delete value2;
				delete value3;
			}

			// user defined type test
			{
				Library::SList<Foo> list;
				std::uint32_t value = rand();
				list.PushFront(Foo(value));
				list.PushFront(Foo(rand()));
				list.PushBack(Foo(rand()));
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				list.PopFront();
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(Foo(value), list.Front());
			}
		}

		TEST_METHOD(TestPushBack)
		{
			// primitive test
			{
				Library::SList<std::uint32_t> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = rand();
				list.PushBack(rand());
				list.PushBack(value);
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(value, list.Back());
			}

			// pointer test
			{
				Library::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value1 = new std::uint32_t(rand());
				std::uint32_t* value2 = new std::uint32_t(rand());
				list.PushBack(value1);
				list.PushBack(value2);
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(value2, list.Back());
				delete value1;
				delete value2;
			}

			// user defined type test
			{
				Library::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = rand();
				list.PushBack(Foo(rand()));
				list.PushBack(Foo(value));
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(Foo(value), list.Back());
			}
		}

		TEST_METHOD(TestFrontReturnsItemInTheFront)
		{
			// primtive type test
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

			// pointer type test
			{
				Library::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value1= new std::uint32_t(rand());
				list.PushFront(value1);
				std::uint32_t* value2 = new std::uint32_t(rand());
				list.PushFront(value2);
				std::uint32_t* value3 = new std::uint32_t(rand());
				list.PushBack(value3);
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				Assert::AreEqual(value2, list.Front());
				delete value1;
				delete value2;
				delete value3;
			}

			// user defined type test
			{
				Library::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				list.PushFront(rand());
				std::uint32_t value = rand();
				list.PushFront(value);
				list.PushBack(rand());
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				Assert::AreEqual(Foo(value), list.Front());
			}
		}

		TEST_METHOD(TestModifyingFrontValue)
		{
			// primitive test
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

			// pointer test
			{
				Library::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value = new std::uint32_t(rand());
				list.PushFront(value);
				Assert::AreEqual(value, list.Front());
				std::uint32_t* newValue = new std::uint32_t(rand());
				list.Front() = newValue;
				Assert::AreEqual(newValue, list.Front());
				delete value;
				delete newValue;
			}

			// user defined type test
			{
				Library::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = rand();
				list.PushFront(Foo(value));
				Assert::AreEqual(Foo(value), list.Front());
				std::uint32_t newValue = rand();
				list.Front() = newValue;
				Assert::AreEqual(Foo(newValue), list.Front());
			}
		}

		TEST_METHOD(TestFrontThrowsExceptionWhenListIsEmpty)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			Assert::ExpectException <std::exception>([&list]() { list.Front(); }, L"Front on empty list did not throw an exception");
		}

		TEST_METHOD(TestBackReturnsItemInTheBack)
		{
			// primitive type test
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

			// pointer type test
			{
				Library::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value1 = new std::uint32_t(rand());
				std::uint32_t* value2 = new std::uint32_t(rand());
				std::uint32_t* value3 = new std::uint32_t(rand());
				list.PushBack(value1);
				list.PushBack(value2);
				list.PushFront(value3);
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				Assert::AreEqual(value2, list.Back());
				delete value1;
				delete value2;
				delete value3;
			}

			// user defined type test
			{
				Library::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = rand();
				list.PushBack(Foo(rand()));
				list.PushBack(Foo(value));
				list.PushFront(Foo(rand()));
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				Assert::AreEqual(Foo(value), list.Back());
			}
		}

		TEST_METHOD(TestBackThrowsExceptionWhenListIsEmpty)
		{
			Library::SList<std::uint32_t> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			Assert::ExpectException <std::exception>([&list]() { list.Front(); }, L"Back on empty list did not throw an exception");
		}

		TEST_METHOD(TestModifyingBackValue)
		{
			// primitive type test
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

			// pointer type test
			{
				Library::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value = new std::uint32_t(rand());
				list.PushBack(value);
				Assert::AreEqual(value, list.Front());
				std::uint32_t* newValue = new std::uint32_t(rand());
				list.Back() = newValue;
				Assert::AreEqual(newValue, list.Back());
				delete value;
				delete newValue;
			}

			// user defined type test
			{
				Library::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = rand();
				list.PushBack(Foo(value));
				Assert::AreEqual(Foo(value), list.Front());
				std::uint32_t newValue = rand();
				list.Back() = Foo(newValue);
				Assert::AreEqual(Foo(newValue), list.Back());
			}
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

		TEST_METHOD(TestBeginAndEnd)
		{
			Library::SList<std::uint32_t> list;
			Assert::IsTrue(list.begin() == list.end());
			std::uint32_t value = rand();
			list.PushFront(value);
			Assert::IsFalse(list.begin() == list.end());
			list.PushBack(rand());
			Assert::AreEqual(list.Front(), *(list.begin()));
		}

		TEST_METHOD(TestFind)
		{
			Library::SList<std::uint32_t> list;
			list.PushFront(rand());
			std::uint32_t value = rand();
			list.PushBack(value);
			list.PushBack(rand());
			Assert::AreEqual(*(list.Find(value)), value);
			Assert::IsFalse(list.Find(value) == list.end());
			std::uint32_t randomValue = rand();
			Assert::IsTrue(list.Find(randomValue) == list.end());
		}

		TEST_METHOD(TestInsertAfter)
		{
			Library::SList<std::uint32_t> list;
			Assert::ExpectException<std::exception>([&list]() { list.InsertAfter(rand(), list.begin()); });
			// check when there is only 1 element
			std::uint32_t frontVal = rand();
			list.PushFront(frontVal);
			std::uint32_t value1 = rand();
			list.InsertAfter(value1, list.begin());
			Assert::AreEqual(value1, list.Back());

			// check when there are 2 and 3 elements
			std::uint32_t backVal = rand();
			list.PushBack(backVal);
			std::uint32_t value2 = rand();
			list.InsertAfter(value2, list.Find(value1));
			Assert::AreEqual(frontVal, *(list.begin()));

			Library::SList<std::uint32_t>::Iterator it = list.begin();
			Assert::AreEqual(value1, *(++it));
			Assert::AreEqual(value2, *(++it));
			Assert::AreEqual(backVal, *(++it));
		}

		TEST_METHOD(TestRemove)
		{
			Library::SList<std::uint32_t> list1;
			// check remove on empty list
			std::uint32_t frontVal = rand();
			list1.Remove(frontVal);
			Assert::IsTrue(list1.IsEmpty());
			
			// check on single item list
			list1.PushFront(frontVal);
			list1.Remove(frontVal);
			Assert::IsTrue(list1.IsEmpty());

			// delete middle element from 3 element list
			Library::SList<std::uint32_t> list2;
			list2.PushFront(frontVal);
			std::uint32_t value1 = rand();
			std::uint32_t backVal = rand();
			list2.PushBack(value1);
			list2.PushBack(backVal);
			Assert::AreEqual(static_cast<std::uint32_t>(3), list2.Size());
			list2.Remove(value1);
			Assert::AreEqual(static_cast<std::uint32_t>(2), list2.Size());
			Assert::AreEqual(frontVal, list2.Front());
			Assert::AreEqual(backVal, list2.Back());
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

