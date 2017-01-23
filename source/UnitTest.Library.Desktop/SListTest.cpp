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
			AnonymousEngine::SList<std::uint32_t>* list1 = new AnonymousEngine::SList<std::uint32_t>();
			Assert::IsNotNull(list1);
			Assert::AreEqual(static_cast<std::uint32_t>(0), list1->Size());
			delete list1;

			// test for pointer type
			AnonymousEngine::SList<std::uint32_t*>* list2 = new AnonymousEngine::SList<std::uint32_t*>();
			Assert::IsNotNull(list2);
			Assert::AreEqual(static_cast<std::uint32_t>(0), list2->Size());
			delete list2;

			// test for user defined type
			AnonymousEngine::SList<Foo>* list3 = new AnonymousEngine::SList<Foo>();
			Assert::IsNotNull(list3);
			Assert::AreEqual(static_cast<std::uint32_t>(0), list3->Size());
			delete list3;
		}

		TEST_METHOD(TestCopyConstructor)
		{
			{
				// test for primitive type
				AnonymousEngine::SList<std::uint32_t> list1;
				list1.PushFront(0);
				list1.PushFront((*mDistribution)(*mGenerator));
				_CrtMemState memStateBeforeAssignment;
				_CrtMemCheckpoint(&memStateBeforeAssignment);

				// Verify that new memory has been allocated and lists are equivalent
				AnonymousEngine::SList<std::uint32_t> list2(list1);
				Assert::IsTrue(DidMemoryStateChange(memStateBeforeAssignment));
				Assert::AreEqual(list1.Size(), list2.Size());
				Assert::AreEqual(list1.Front(), list2.Front());
				Assert::AreEqual(list1.Back(), list2.Back());
			}

			{
				// test for pointer type
				AnonymousEngine::SList<std::uint32_t*> list1;
				std::uint32_t* value1 = new std::uint32_t(0);
				std::uint32_t* value2 = new std::uint32_t((*mDistribution)(*mGenerator));
				list1.PushFront(value1);
				list1.PushFront(value2);
				_CrtMemState memStateBeforeAssignment;
				_CrtMemCheckpoint(&memStateBeforeAssignment);

				// Verify that new memory has been allocated and lists are equivalent
				AnonymousEngine::SList<std::uint32_t*> list2(list1);
				Assert::IsTrue(DidMemoryStateChange(memStateBeforeAssignment));
				Assert::AreEqual(list1.Size(), list2.Size());
				Assert::AreEqual(list1.Front(), list2.Front());
				Assert::AreEqual(list1.Back(), list2.Back());
				delete value1;
				delete value2;
			}

			{
				// test for user defined type
				AnonymousEngine::SList<Foo> list1;
				list1.PushFront(Foo(0));
				list1.PushFront(Foo((*mDistribution)(*mGenerator)));
				_CrtMemState memStateBeforeAssignment;
				_CrtMemCheckpoint(&memStateBeforeAssignment);

				// Verify that new memory has been allocated and lists are equivalent
				AnonymousEngine::SList<Foo> list2(list1);
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
				AnonymousEngine::SList<std::uint32_t> list1;
				AnonymousEngine::SList<std::uint32_t> list2;
				
				list1.PushFront((*mDistribution)(*mGenerator));
				list1.PushFront((*mDistribution)(*mGenerator));
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
				AnonymousEngine::SList<std::uint32_t*> list1;
				AnonymousEngine::SList<std::uint32_t*> list2;

				std::uint32_t* value1 = new std::uint32_t((*mDistribution)(*mGenerator));
				std::uint32_t* value2 = new std::uint32_t((*mDistribution)(*mGenerator));
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
				AnonymousEngine::SList<Foo> list1;
				AnonymousEngine::SList<Foo> list2;

				list1.PushFront(Foo((*mDistribution)(*mGenerator)));
				list1.PushFront(Foo((*mDistribution)(*mGenerator)));
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
				AnonymousEngine::SList<std::uint32_t> list1;

				list1.PushFront((*mDistribution)(*mGenerator));
				list1.PushFront((*mDistribution)(*mGenerator));
				_CrtMemState memStateBeforeAssignment;
				_CrtMemCheckpoint(&memStateBeforeAssignment);

				// Verify that no new memory has been allocated
				list1 = list1;
				Assert::IsFalse(DidMemoryStateChange(memStateBeforeAssignment));
			}

			// pointer test
			{
				AnonymousEngine::SList<std::uint32_t*> list1;
				std::uint32_t* value1 = new std::uint32_t((*mDistribution)(*mGenerator));
				std::uint32_t* value2 = new std::uint32_t((*mDistribution)(*mGenerator));
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
				AnonymousEngine::SList<Foo> list1;

				list1.PushFront(Foo((*mDistribution)(*mGenerator)));
				list1.PushFront(Foo((*mDistribution)(*mGenerator)));
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
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront((*mDistribution)(*mGenerator));
				list.PushFront(value);
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(value, list.Front());
			}

			// pointer test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value1 = new std::uint32_t((*mDistribution)(*mGenerator));
				std::uint32_t* value2 = new std::uint32_t((*mDistribution)(*mGenerator));
				list.PushFront(value1);
				list.PushFront(value2);
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(value2, list.Front());
				delete value1;
				delete value2;
			}

			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(Foo((*mDistribution)(*mGenerator)));
				list.PushFront(Foo(value));
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(Foo(value), list.Front());
			}
		}

		TEST_METHOD(TestPopFrontRemovesItemAndUpdatesSize)
		{
			// primitive test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(value);
				list.PushFront((*mDistribution)(*mGenerator));
				list.PushBack((*mDistribution)(*mGenerator));
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				list.PopFront();
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(value, list.Front());
			}

			// pointer test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				std::uint32_t* value1 = new std::uint32_t((*mDistribution)(*mGenerator));
				std::uint32_t* value2 = new std::uint32_t((*mDistribution)(*mGenerator));
				std::uint32_t* value3 = new std::uint32_t((*mDistribution)(*mGenerator));
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
				AnonymousEngine::SList<Foo> list;
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(Foo(value));
				list.PushFront(Foo((*mDistribution)(*mGenerator)));
				list.PushBack(Foo((*mDistribution)(*mGenerator)));
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
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushBack((*mDistribution)(*mGenerator));
				list.PushBack(value);
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(value, list.Back());
			}

			// pointer test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value1 = new std::uint32_t((*mDistribution)(*mGenerator));
				std::uint32_t* value2 = new std::uint32_t((*mDistribution)(*mGenerator));
				list.PushBack(value1);
				list.PushBack(value2);
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(value2, list.Back());
				delete value1;
				delete value2;
			}

			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushBack(Foo((*mDistribution)(*mGenerator)));
				list.PushBack(Foo(value));
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				Assert::AreEqual(Foo(value), list.Back());
			}
		}

		TEST_METHOD(TestFrontReturnsItemInTheFront)
		{
			// primtive type test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				list.PushFront((*mDistribution)(*mGenerator));
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(value);
				list.PushBack((*mDistribution)(*mGenerator));
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				const AnonymousEngine::SList<std::uint32_t> constList(list);
				Assert::AreEqual(value, list.Front());
				Assert::AreEqual(value, constList.Front());
			}

			// pointer type test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value1= new std::uint32_t((*mDistribution)(*mGenerator));
				list.PushFront(value1);
				std::uint32_t* value2 = new std::uint32_t((*mDistribution)(*mGenerator));
				list.PushFront(value2);
				std::uint32_t* value3 = new std::uint32_t((*mDistribution)(*mGenerator));
				list.PushBack(value3);
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				const AnonymousEngine::SList<std::uint32_t*> constList(list);
				Assert::AreEqual(value2, list.Front());
				Assert::AreEqual(value2, constList.Front());
				delete value1;
				delete value2;
				delete value3;
			}

			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				list.PushFront((*mDistribution)(*mGenerator));
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(value);
				list.PushBack((*mDistribution)(*mGenerator));
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				const AnonymousEngine::SList<Foo> constList(list);
				Assert::AreEqual(Foo(value), list.Front());
				Assert::AreEqual(Foo(value), constList.Front());
			}
		}

		TEST_METHOD(TestModifyingFrontValue)
		{
			// primitive test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(value);
				Assert::AreEqual(value, list.Front());
				std::uint32_t newValue = (*mDistribution)(*mGenerator);
				list.Front() = newValue;
				Assert::AreEqual(newValue, list.Front());
			}

			// pointer test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value = new std::uint32_t((*mDistribution)(*mGenerator));
				list.PushFront(value);
				Assert::AreEqual(value, list.Front());
				std::uint32_t* newValue = new std::uint32_t((*mDistribution)(*mGenerator));
				list.Front() = newValue;
				Assert::AreEqual(newValue, list.Front());
				delete value;
				delete newValue;
			}

			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(Foo(value));
				Assert::AreEqual(Foo(value), list.Front());
				std::uint32_t newValue = (*mDistribution)(*mGenerator);
				list.Front() = newValue;
				Assert::AreEqual(Foo(newValue), list.Front());
			}
		}

		TEST_METHOD(TestFrontThrowsExceptionWhenListIsEmpty)
		{
			// primitive type test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				const AnonymousEngine::SList<std::uint32_t> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Front(); }, L"Front on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Front(); }, L"Front on empty list did not throw an exception");
			}

			// pointer type test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				const AnonymousEngine::SList<std::uint32_t*> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Front(); }, L"Front on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Front(); }, L"Front on empty list did not throw an exception");
			}

			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				const AnonymousEngine::SList<Foo> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Front(); }, L"Front on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Front(); }, L"Front on empty list did not throw an exception");
			}
		}

		TEST_METHOD(TestBackReturnsItemInTheBack)
		{
			// primitive type test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushBack((*mDistribution)(*mGenerator));
				list.PushBack(value);
				list.PushFront((*mDistribution)(*mGenerator));
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				const AnonymousEngine::SList<std::uint32_t> constList(list);
				Assert::AreEqual(value, list.Back());
				Assert::AreEqual(value, constList.Back());
			}

			// pointer type test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value1 = new std::uint32_t((*mDistribution)(*mGenerator));
				std::uint32_t* value2 = new std::uint32_t((*mDistribution)(*mGenerator));
				std::uint32_t* value3 = new std::uint32_t((*mDistribution)(*mGenerator));
				list.PushBack(value1);
				list.PushBack(value2);
				list.PushFront(value3);
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				const AnonymousEngine::SList<std::uint32_t*> constList(list);
				Assert::AreEqual(value2, list.Back());
				Assert::AreEqual(value2, constList.Back());
				delete value1;
				delete value2;
				delete value3;
			}

			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushBack(Foo((*mDistribution)(*mGenerator)));
				list.PushBack(Foo(value));
				list.PushFront(Foo((*mDistribution)(*mGenerator)));
				Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
				const AnonymousEngine::SList<Foo> constList(list);
				Assert::AreEqual(Foo(value), list.Back());
				Assert::AreEqual(Foo(value), constList.Back());
			}
		}

		TEST_METHOD(TestBackThrowsExceptionWhenListIsEmpty)
		{
			{
				AnonymousEngine::SList<std::uint32_t> list;
				const AnonymousEngine::SList<std::uint32_t> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Back(); }, L"Back on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Back(); }, L"Front on empty list did not throw an exception");
			}

			{
				AnonymousEngine::SList<std::uint32_t*> list;
				const AnonymousEngine::SList<std::uint32_t*> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Back(); }, L"Back on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Back(); }, L"Front on empty list did not throw an exception");
			}

			{
				AnonymousEngine::SList<Foo> list;
				const AnonymousEngine::SList<Foo> constList;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				Assert::ExpectException <std::exception>([&list]() { list.Back(); }, L"Back on empty list did not throw an exception");
				Assert::ExpectException <std::exception>([&constList]() { constList.Back(); }, L"Front on empty list did not throw an exception");
			}
		}

		TEST_METHOD(TestModifyingBackValue)
		{
			// primitive type test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushBack(value);
				Assert::AreEqual(value, list.Front());
				std::uint32_t newValue = (*mDistribution)(*mGenerator);
				list.Back() = newValue;
				Assert::AreEqual(newValue, list.Back());
			}

			// pointer type test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t* value = new std::uint32_t((*mDistribution)(*mGenerator));
				list.PushBack(value);
				Assert::AreEqual(value, list.Front());
				std::uint32_t* newValue = new std::uint32_t((*mDistribution)(*mGenerator));
				list.Back() = newValue;
				Assert::AreEqual(newValue, list.Back());
				delete value;
				delete newValue;
			}

			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushBack(Foo(value));
				Assert::AreEqual(Foo(value), list.Front());
				std::uint32_t newValue = (*mDistribution)(*mGenerator);
				list.Back() = Foo(newValue);
				Assert::AreEqual(Foo(newValue), list.Back());
			}
		}

		TEST_METHOD(TestSizeMethod)
		{
			// primitive type
			{
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				list.PushBack((*mDistribution)(*mGenerator));
				Assert::AreEqual(static_cast<std::uint32_t>(1), list.Size());
				list.PushFront((*mDistribution)(*mGenerator));
				Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
				list.PopFront();
				Assert::AreEqual(static_cast<std::uint32_t>(1), list.Size());
				list.PopFront();
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			}
			// pointer type
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushBack(&value);
				Assert::AreEqual(static_cast<std::uint32_t>(1), list.Size());
				list.Clear();
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			}
			// user defined type
			{
				AnonymousEngine::SList<Foo> list;
				Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
				std::uint32_t value = (*mDistribution)(*mGenerator);
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
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::IsTrue(list.IsEmpty());
				list.PushBack((*mDistribution)(*mGenerator));
				Assert::IsFalse(list.IsEmpty());
				list.PopFront();
				Assert::IsTrue(list.IsEmpty());
			}
			// pointer type
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				Assert::IsTrue(list.IsEmpty());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushBack(&value);
				Assert::IsFalse(list.IsEmpty());
				list.PopFront();
				Assert::IsTrue(list.IsEmpty());
			}
			// user defined type
			{
				AnonymousEngine::SList<Foo> list;
				Assert::IsTrue(list.IsEmpty());
				list.PushBack(Foo((*mDistribution)(*mGenerator)));
				Assert::IsFalse(list.IsEmpty());
				list.PopFront();
				Assert::IsTrue(list.IsEmpty());
			}
		}

		TEST_METHOD(TestClear)
		{
			// primtive type
			{
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::IsTrue(list.IsEmpty());
				list.PushBack((*mDistribution)(*mGenerator));
				list.PushFront((*mDistribution)(*mGenerator));
				Assert::IsFalse(list.IsEmpty());
				list.Clear();
				Assert::IsTrue(list.IsEmpty());
			}
			// pointer type
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				Assert::IsTrue(list.IsEmpty());
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				list.PushBack(&value1);
				list.PushFront(&value2);
				Assert::IsFalse(list.IsEmpty());
				list.Clear();
				Assert::IsTrue(list.IsEmpty());
			}
			// user defined type
			{
				AnonymousEngine::SList<Foo> list;
				Assert::IsTrue(list.IsEmpty());
				list.PushBack(Foo((*mDistribution)(*mGenerator)));
				list.PushFront(Foo((*mDistribution)(*mGenerator)));
				Assert::IsFalse(list.IsEmpty());
				list.Clear();
				Assert::IsTrue(list.IsEmpty());
			}
		}

		TEST_METHOD(TestBeginAndEnd)
		{
			// primitive type
			{
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::IsTrue(list.begin() == list.end());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(value);
				Assert::IsFalse(list.begin() == list.end());
				list.PushBack((*mDistribution)(*mGenerator));
				Assert::AreEqual(list.Front(), *(list.begin()));
			}
			// pointer type
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				Assert::IsTrue(list.begin() == list.end());
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				list.PushFront(&value1);
				Assert::IsFalse(list.begin() == list.end());
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				list.PushBack(&value2);
				Assert::AreEqual(list.Front(), *(list.begin()));
			}
			// user defined type
			{
				AnonymousEngine::SList<Foo> list;
				Assert::IsTrue(list.begin() == list.end());
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(Foo(value));
				Assert::IsFalse(list.begin() == list.end());
				list.PushBack(Foo((*mDistribution)(*mGenerator)));
				Assert::AreEqual(list.Front(), *(list.begin()));
			}
		}

		TEST_METHOD(TestFind)
		{
			// primitive type
			{
				AnonymousEngine::SList<std::uint32_t> list;
				// test on empty list
				std::uint32_t value = (*mDistribution)(*mGenerator);
				Assert::IsTrue(list.Find(value) == list.end());

				// test on list with 1 element
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				list.PushFront(value1);
				Assert::AreEqual(*(list.Find(value1)), value1);

				// test on list with multiple element
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				list.PushBack(value2);
				list.PushBack((*mDistribution)(*mGenerator));
				Assert::AreEqual(*(list.Find(value2)), value2);
				Assert::IsFalse(list.Find(value2) == list.end());
				std::uint32_t randomValue = (*mDistribution)(*mGenerator);
				Assert::IsTrue(list.Find(randomValue) == list.end());
			}
			// pointer type
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				// test on empty list
				std::uint32_t value = (*mDistribution)(*mGenerator);
				std::uint32_t *valuePtr = &value;
				Assert::IsTrue(list.Find(valuePtr) == list.end());

				// test on list with 1 element
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t *value1Ptr = &value1;
				list.PushFront(&value1);
				Assert::AreEqual(*(list.Find(value1Ptr)), &value1);

				// test on list with multiple element
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				std::uint32_t value3 = (*mDistribution)(*mGenerator);
				std::uint32_t *value2Ptr = &value2;
				std::uint32_t *value3Ptr = &value3;
				list.PushBack(value2Ptr);
				list.PushBack(value3Ptr);
				Assert::AreEqual(*(list.Find(value2Ptr)), value2Ptr);
				Assert::IsFalse(list.Find(value2Ptr) == list.end());
				std::uint32_t randomValue = (*mDistribution)(*mGenerator);
				std::uint32_t* randomValuePtr = &randomValue;
				Assert::IsTrue(list.Find(randomValuePtr) == list.end());
			}
			// user defined type
			{
				AnonymousEngine::SList<Foo> list;
				// test on empty list
				Foo value = Foo((*mDistribution)(*mGenerator));
				Assert::IsTrue(list.Find(value) == list.end());

				// test on list with 1 element
				Foo value1 = Foo((*mDistribution)(*mGenerator));
				list.PushFront(value1);
				Assert::AreEqual(*(list.Find(value1)), value1);

				// test on list with multiple element
				Foo value2 = Foo((*mDistribution)(*mGenerator));
				list.PushBack(value2);
				list.PushBack((*mDistribution)(*mGenerator));
				Assert::AreEqual(*(list.Find(value2)), value2);
				Assert::IsFalse(list.Find(value2) == list.end());
				Foo randomValue = Foo((*mDistribution)(*mGenerator));
				Assert::IsTrue(list.Find(randomValue) == list.end());
			}
		}

		TEST_METHOD(TestInsertAfter)
		{
			// primitive type test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				Assert::ExpectException<std::exception>([&list]() { list.InsertAfter((*mDistribution)(*mGenerator), list.begin()); });
				// check when there is only 1 element
				std::uint32_t frontVal = (*mDistribution)(*mGenerator);
				list.PushFront(frontVal);
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				list.InsertAfter(value1, list.begin());
				Assert::AreEqual(value1, list.Back());

				// check when there are 2 and 3 elements
				std::uint32_t backVal = (*mDistribution)(*mGenerator);
				list.PushBack(backVal);
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				list.InsertAfter(value2, list.Find(value1));
				Assert::AreEqual(frontVal, *(list.begin()));

				AnonymousEngine::SList<std::uint32_t>::Iterator it = list.begin();
				Assert::AreEqual(value1, *(++it));
				Assert::AreEqual(value2, *(++it));
				Assert::AreEqual(backVal, *(++it));
			}
			// pointer type test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				std::uint32_t value = (*mDistribution)(*mGenerator);
				std::uint32_t* valuePtr = &value;
				Assert::ExpectException<std::exception>([&list, valuePtr]() { list.InsertAfter(valuePtr, list.begin()); });
				// check when there is only 1 element
				std::uint32_t frontVal = (*mDistribution)(*mGenerator);
				list.PushFront(&frontVal);
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				list.InsertAfter(&value1, list.begin());
				Assert::AreEqual(&value1, list.Back());

				// check when there are 2 and 3 elements
				std::uint32_t backVal = (*mDistribution)(*mGenerator);
				list.PushBack(&backVal);
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				std::uint32_t* value1Ptr = &value1;
				list.InsertAfter(&value2, list.Find(value1Ptr));
				Assert::AreEqual(&frontVal, *(list.begin()));

				AnonymousEngine::SList<std::uint32_t*>::Iterator it = list.begin();
				Assert::AreEqual(&value1, *(++it));
				Assert::AreEqual(&value2, *(++it));
				Assert::AreEqual(&backVal, *(++it));
			}
			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				Assert::ExpectException<std::exception>([&list]() { list.InsertAfter((*mDistribution)(*mGenerator), list.begin()); });
				// check when there is only 1 element
				Foo frontVal = Foo((*mDistribution)(*mGenerator));
				list.PushFront(frontVal);
				Foo value1 = Foo((*mDistribution)(*mGenerator));
				list.InsertAfter(value1, list.begin());
				Assert::AreEqual(value1, list.Back());

				// check when there are 2 and 3 elements
				Foo backVal = Foo((*mDistribution)(*mGenerator));
				list.PushBack(backVal);
				Foo value2 = Foo((*mDistribution)(*mGenerator));
				list.InsertAfter(value2, list.Find(value1));
				Assert::AreEqual(frontVal, *(list.begin()));

				AnonymousEngine::SList<Foo>::Iterator it = list.begin();
				Assert::AreEqual(value1, *(++it));
				Assert::AreEqual(value2, *(++it));
				Assert::AreEqual(backVal, *(++it));
			}
		}

		TEST_METHOD(TestRemove)
		{
			// primitive type test
			{
				AnonymousEngine::SList<std::uint32_t> list1;
				// check remove on empty list
				std::uint32_t frontVal = (*mDistribution)(*mGenerator);
				list1.Remove(frontVal);
				Assert::IsTrue(list1.IsEmpty());

				// check on single item list
				list1.PushFront(frontVal);
				list1.Remove(frontVal);
				Assert::IsTrue(list1.IsEmpty());

				// check on 2 items list
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list1.PushFront((*mDistribution)(*mGenerator));
				list1.PushBack(value);
				list1.Remove(value);
				Assert::AreNotEqual(value, list1.Back());
				Assert::AreEqual(static_cast<std::uint32_t>(1), list1.Size());

				// delete middle element from 3 element list
				AnonymousEngine::SList<std::uint32_t> list2;
				list2.PushFront(frontVal);
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t backVal = (*mDistribution)(*mGenerator);
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
				AnonymousEngine::SList<std::uint32_t*> list1;
				// check remove on empty list
				std::uint32_t frontVal = (*mDistribution)(*mGenerator);
				std::uint32_t* frontValPtr = &frontVal;
				list1.Remove(frontValPtr);
				Assert::IsTrue(list1.IsEmpty());

				// check on single item list
				list1.PushFront(frontValPtr);
				list1.Remove(frontValPtr);
				Assert::IsTrue(list1.IsEmpty());

				// check on 2 items list
				std::uint32_t value = (*mDistribution)(*mGenerator);
				std::uint32_t* valuePtr = &value;
				std::uint32_t randomValue = (*mDistribution)(*mGenerator);
				std::uint32_t* randomValuePtr = &randomValue;
				list1.PushFront(randomValuePtr);
				list1.PushBack(valuePtr);
				list1.Remove(valuePtr);
				Assert::AreNotEqual(valuePtr, list1.Back());
				Assert::AreEqual(static_cast<std::uint32_t>(1), list1.Size());

				// delete middle element from 3 element list
				AnonymousEngine::SList<std::uint32_t*> list2;
				list2.PushFront(frontValPtr);
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t* value1Ptr = &value1;
				std::uint32_t backVal = (*mDistribution)(*mGenerator);
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
				AnonymousEngine::SList<Foo> list1;
				// check remove on empty list
				Foo frontVal = Foo((*mDistribution)(*mGenerator));
				list1.Remove(frontVal);
				Assert::IsTrue(list1.IsEmpty());

				// check on single item list
				list1.PushFront(frontVal);
				list1.Remove(frontVal);
				Assert::IsTrue(list1.IsEmpty());

				// check on 2 items list
				Foo value = (*mDistribution)(*mGenerator);
				list1.PushFront((*mDistribution)(*mGenerator));
				list1.PushBack(value);
				list1.Remove(value);
				Assert::AreNotEqual(value, list1.Back());
				Assert::AreEqual(static_cast<std::uint32_t>(1), list1.Size());

				// delete middle element from 3 element list
				AnonymousEngine::SList<Foo> list2;
				list2.PushFront(frontVal);
				Foo value1 = Foo((*mDistribution)(*mGenerator));
				Foo backVal = Foo((*mDistribution)(*mGenerator));
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
			std::random_device mDevice;
			mGenerator = new std::default_random_engine(mDevice());
			mDistribution = new std::uniform_int_distribution<std::uint32_t>(0, UINT32_MAX);
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

		TEST_CLASS_CLEANUP(EndClass)
		{
			delete mGenerator;
			delete mDistribution;
		}
	private:
		_CrtMemState mStartMemState;
		static std::default_random_engine* mGenerator;
		static std::uniform_int_distribution<std::uint32_t>* mDistribution;

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

	std::default_random_engine* SListTest::mGenerator;
	std::uniform_int_distribution<std::uint32_t>* SListTest::mDistribution;
}

