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
				const Library::SList<std::uint32_t> constList(list);
				Assert::AreEqual(value, list.Front());
				Assert::AreEqual(value, constList.Front());
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
				const Library::SList<std::uint32_t*> constList(list);
				Assert::AreEqual(value2, list.Front());
				Assert::AreEqual(value2, constList.Front());
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
				const Library::SList<Foo> constList(list);
				Assert::AreEqual(Foo(value), list.Front());
				Assert::AreEqual(Foo(value), constList.Front());
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
			// primitive type test
			{
				Library::SList<std::uint32_t> list;
				const Library::SList<std::uint32_t> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Front(); }, L"Front on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Front(); }, L"Front on empty list did not throw an exception");
			}

			// pointer type test
			{
				Library::SList<std::uint32_t*> list;
				const Library::SList<std::uint32_t*> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Front(); }, L"Front on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Front(); }, L"Front on empty list did not throw an exception");
			}

			// user defined type test
			{
				Library::SList<Foo> list;
				const Library::SList<Foo> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Front(); }, L"Front on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Front(); }, L"Front on empty list did not throw an exception");
			}
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
				const Library::SList<std::uint32_t> constList(list);
				Assert::AreEqual(value, list.Back());
				Assert::AreEqual(value, constList.Back());
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
				const Library::SList<std::uint32_t*> constList(list);
				Assert::AreEqual(value2, list.Back());
				Assert::AreEqual(value2, constList.Back());
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
				const Library::SList<Foo> constList(list);
				Assert::AreEqual(Foo(value), list.Back());
				Assert::AreEqual(Foo(value), constList.Back());
			}
		}

		TEST_METHOD(TestBackThrowsExceptionWhenListIsEmpty)
		{
			{
				Library::SList<std::uint32_t> list;
				const Library::SList<std::uint32_t> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Back(); }, L"Back on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Back(); }, L"Front on empty list did not throw an exception");
			}

			{
				Library::SList<std::uint32_t*> list;
				const Library::SList<std::uint32_t*> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Back(); }, L"Back on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Back(); }, L"Front on empty list did not throw an exception");
			}

			{
				Library::SList<Foo> list;
				const Library::SList<Foo> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Back(); }, L"Back on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Back(); }, L"Front on empty list did not throw an exception");
			}
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
			// primitive type
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
			// pointer type
			{
				Library::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = rand();
				list.PushBack(&value);
				Assert::AreEqual(static_cast<std::uint32_t>(1), list.Size());
				list.Clear();
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			}
			// user defined type
			{
				Library::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = rand();
				list.PushBack(Foo(value));
				Assert::AreEqual(static_cast<std::uint32_t>(1), list.Size());
				list.Clear();
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			}
		}

		TEST_METHOD(TestEmptyMethod)
		{
			// primtive type
			{
				Library::SList<std::uint32_t> list;
				Assert::IsTrue(list.IsEmpty());
				list.PushBack(rand());
				Assert::IsFalse(list.IsEmpty());
				list.PopFront();
				Assert::IsTrue(list.IsEmpty());
			}
			// pointer type
			{
				Library::SList<std::uint32_t*> list;
				Assert::IsTrue(list.IsEmpty());
				std::uint32_t value = rand();
				list.PushBack(&value);
				Assert::IsFalse(list.IsEmpty());
				list.PopFront();
				Assert::IsTrue(list.IsEmpty());
			}
			// user defined type
			{
				Library::SList<Foo> list;
				Assert::IsTrue(list.IsEmpty());
				list.PushBack(Foo(rand()));
				Assert::IsFalse(list.IsEmpty());
				list.PopFront();
				Assert::IsTrue(list.IsEmpty());
			}
		}

		TEST_METHOD(TestClear)
		{
			// primtive type
			{
				Library::SList<std::uint32_t> list;
				Assert::IsTrue(list.IsEmpty());
				list.PushBack(rand());
				list.PushFront(rand());
				Assert::IsFalse(list.IsEmpty());
				list.Clear();
				Assert::IsTrue(list.IsEmpty());
			}
			// pointer type
			{
				Library::SList<std::uint32_t*> list;
				Assert::IsTrue(list.IsEmpty());
				std::uint32_t value1 = rand();
				std::uint32_t value2 = rand();
				list.PushBack(&value1);
				list.PushFront(&value2);
				Assert::IsFalse(list.IsEmpty());
				list.Clear();
				Assert::IsTrue(list.IsEmpty());
			}
			// user defined type
			{
				Library::SList<Foo> list;
				Assert::IsTrue(list.IsEmpty());
				list.PushBack(Foo(rand()));
				list.PushFront(Foo(rand()));
				Assert::IsFalse(list.IsEmpty());
				list.Clear();
				Assert::IsTrue(list.IsEmpty());
			}
		}

		TEST_METHOD(TestBeginAndEnd)
		{
			// primitive type
			{
				Library::SList<std::uint32_t> list;
				Assert::IsTrue(list.begin() == list.end());
				std::uint32_t value = rand();
				list.PushFront(value);
				Assert::IsFalse(list.begin() == list.end());
				list.PushBack(rand());
				Assert::AreEqual(list.Front(), *(list.begin()));
			}
			// pointer type
			{
				Library::SList<std::uint32_t*> list;
				Assert::IsTrue(list.begin() == list.end());
				std::uint32_t value1 = rand();
				list.PushFront(&value1);
				Assert::IsFalse(list.begin() == list.end());
				std::uint32_t value2 = rand();
				list.PushBack(&value2);
				Assert::AreEqual(list.Front(), *(list.begin()));
			}
			// user defined type
			{
				Library::SList<Foo> list;
				Assert::IsTrue(list.begin() == list.end());
				std::uint32_t value = rand();
				list.PushFront(Foo(value));
				Assert::IsFalse(list.begin() == list.end());
				list.PushBack(Foo(rand()));
				Assert::AreEqual(list.Front(), *(list.begin()));
			}
		}

		TEST_METHOD(TestFind)
		{
			// primitive type
			{
				Library::SList<std::uint32_t> list;
				// test on empty list
				std::uint32_t value = rand();
				Assert::IsTrue(list.Find(value) == list.end());

				// test on list with 1 element
				std::uint32_t value1 = rand();
				list.PushFront(value1);
				Assert::AreEqual(*(list.Find(value1)), value1);

				// test on list with multiple element
				std::uint32_t value2 = rand();
				list.PushBack(value2);
				list.PushBack(rand());
				Assert::AreEqual(*(list.Find(value2)), value2);
				Assert::IsFalse(list.Find(value2) == list.end());
				std::uint32_t randomValue = rand();
				Assert::IsTrue(list.Find(randomValue) == list.end());
			}
			// pointer type
			{
				Library::SList<std::uint32_t*> list;
				// test on empty list
				std::uint32_t value = rand();
				std::uint32_t *valuePtr = &value;
				Assert::IsTrue(list.Find(valuePtr) == list.end());

				// test on list with 1 element
				std::uint32_t value1 = rand();
				std::uint32_t *value1Ptr = &value1;
				list.PushFront(&value1);
				Assert::AreEqual(*(list.Find(value1Ptr)), &value1);

				// test on list with multiple element
				std::uint32_t value2 = rand();
				std::uint32_t value3 = rand();
				std::uint32_t *value2Ptr = &value2;
				std::uint32_t *value3Ptr = &value3;
				list.PushBack(value2Ptr);
				list.PushBack(value3Ptr);
				Assert::AreEqual(*(list.Find(value2Ptr)), value2Ptr);
				Assert::IsFalse(list.Find(value2Ptr) == list.end());
				std::uint32_t randomValue = rand();
				std::uint32_t* randomValuePtr = &randomValue;
				Assert::IsTrue(list.Find(randomValuePtr) == list.end());
			}
			// user defined type
			{
				Library::SList<Foo> list;
				// test on empty list
				Foo value = Foo(rand());
				Assert::IsTrue(list.Find(value) == list.end());

				// test on list with 1 element
				Foo value1 = Foo(rand());
				list.PushFront(value1);
				Assert::AreEqual(*(list.Find(value1)), value1);

				// test on list with multiple element
				Foo value2 = Foo(rand());
				list.PushBack(value2);
				list.PushBack(rand());
				Assert::AreEqual(*(list.Find(value2)), value2);
				Assert::IsFalse(list.Find(value2) == list.end());
				Foo randomValue = Foo(rand());
				Assert::IsTrue(list.Find(randomValue) == list.end());
			}
		}

		TEST_METHOD(TestInsertAfter)
		{
			// primitive type test
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
			// pointer type test
			{
				Library::SList<std::uint32_t*> list;
				std::uint32_t value = rand();
				std::uint32_t* valuePtr = &value;
				Assert::ExpectException<std::exception>([&list, valuePtr]() { list.InsertAfter(valuePtr, list.begin()); });
				// check when there is only 1 element
				std::uint32_t frontVal = rand();
				list.PushFront(&frontVal);
				std::uint32_t value1 = rand();
				list.InsertAfter(&value1, list.begin());
				Assert::AreEqual(&value1, list.Back());

				// check when there are 2 and 3 elements
				std::uint32_t backVal = rand();
				list.PushBack(&backVal);
				std::uint32_t value2 = rand();
				std::uint32_t* value1Ptr = &value1;
				list.InsertAfter(&value2, list.Find(value1Ptr));
				Assert::AreEqual(&frontVal, *(list.begin()));

				Library::SList<std::uint32_t*>::Iterator it = list.begin();
				Assert::AreEqual(&value1, *(++it));
				Assert::AreEqual(&value2, *(++it));
				Assert::AreEqual(&backVal, *(++it));
			}
			// user defined type test
			{
				Library::SList<Foo> list;
				Assert::ExpectException<std::exception>([&list]() { list.InsertAfter(rand(), list.begin()); });
				// check when there is only 1 element
				Foo frontVal = Foo(rand());
				list.PushFront(frontVal);
				Foo value1 = Foo(rand());
				list.InsertAfter(value1, list.begin());
				Assert::AreEqual(value1, list.Back());

				// check when there are 2 and 3 elements
				Foo backVal = Foo(rand());
				list.PushBack(backVal);
				Foo value2 = Foo(rand());
				list.InsertAfter(value2, list.Find(value1));
				Assert::AreEqual(frontVal, *(list.begin()));

				Library::SList<Foo>::Iterator it = list.begin();
				Assert::AreEqual(value1, *(++it));
				Assert::AreEqual(value2, *(++it));
				Assert::AreEqual(backVal, *(++it));
			}
		}

		TEST_METHOD(TestRemove)
		{
			// primitive type test
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

				// check on 2 items list
				std::uint32_t value = rand();
				list1.PushFront(rand());
				list1.PushBack(value);
				list1.Remove(value);
				Assert::AreNotEqual(value, list1.Back());
				Assert::AreEqual(static_cast<std::uint32_t>(1), list1.Size());

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
			// pointer type test
			{
				Library::SList<std::uint32_t*> list1;
				// check remove on empty list
				std::uint32_t frontVal = rand();
				std::uint32_t* frontValPtr = &frontVal;
				list1.Remove(frontValPtr);
				Assert::IsTrue(list1.IsEmpty());

				// check on single item list
				list1.PushFront(frontValPtr);
				list1.Remove(frontValPtr);
				Assert::IsTrue(list1.IsEmpty());

				// check on 2 items list
				std::uint32_t value = rand();
				std::uint32_t* valuePtr = &value;
				std::uint32_t randomValue = rand();
				std::uint32_t* randomValuePtr = &randomValue;
				list1.PushFront(randomValuePtr);
				list1.PushBack(valuePtr);
				list1.Remove(valuePtr);
				Assert::AreNotEqual(valuePtr, list1.Back());
				Assert::AreEqual(static_cast<std::uint32_t>(1), list1.Size());

				// delete middle element from 3 element list
				Library::SList<std::uint32_t*> list2;
				list2.PushFront(frontValPtr);
				std::uint32_t value1 = rand();
				std::uint32_t* value1Ptr = &value1;
				std::uint32_t backVal = rand();
				std::uint32_t* backValPtr = &backVal;
				list2.PushBack(value1Ptr);
				list2.PushBack(backValPtr);
				Assert::AreEqual(static_cast<std::uint32_t>(3), list2.Size());
				list2.Remove(value1Ptr);
				Assert::AreEqual(static_cast<std::uint32_t>(2), list2.Size());
				Assert::AreEqual(frontValPtr, list2.Front());
				Assert::AreEqual(backValPtr, list2.Back());
			}
			// user defined type test
			{
				Library::SList<Foo> list1;
				// check remove on empty list
				Foo frontVal = Foo(rand());
				list1.Remove(frontVal);
				Assert::IsTrue(list1.IsEmpty());

				// check on single item list
				list1.PushFront(frontVal);
				list1.Remove(frontVal);
				Assert::IsTrue(list1.IsEmpty());

				// check on 2 items list
				Foo value = rand();
				list1.PushFront(rand());
				list1.PushBack(value);
				list1.Remove(value);
				Assert::AreNotEqual(value, list1.Back());
				Assert::AreEqual(static_cast<std::uint32_t>(1), list1.Size());

				// delete middle element from 3 element list
				Library::SList<Foo> list2;
				list2.PushFront(frontVal);
				Foo value1 = Foo(rand());
				Foo backVal = Foo(rand());
				list2.PushBack(value1);
				list2.PushBack(backVal);
				Assert::AreEqual(static_cast<std::uint32_t>(3), list2.Size());
				list2.Remove(value1);
				Assert::AreEqual(static_cast<std::uint32_t>(2), list2.Size());
				Assert::AreEqual(frontVal, list2.Front());
				Assert::AreEqual(backVal, list2.Back());
				Foo randomFoo;
			}
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

