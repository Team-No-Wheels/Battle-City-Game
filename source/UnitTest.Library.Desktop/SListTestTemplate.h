#pragma once

#include "Foo.h"
#include "CppUnitTestAssert.h"
#include "SList.h"

namespace UnitTestLibraryDesktop
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	template <typename T>
	class SListTestTemplate
	{
	public:
		static void TestDefaultConstructor()
		{
			AnonymousEngine::SList<T>* list1 = new AnonymousEngine::SList<T>();
			Assert::IsNotNull(list1);
			Assert::AreEqual(static_cast<std::uint32_t>(0), list1->Size());
			delete list1;
		}

		static void TestCopyConstructor(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list1;
			list1.PushFront(value1);
			list1.PushFront(value2);

			// Verify that new memory has been allocated and lists are equivalent
			AnonymousEngine::SList<T> list2(list1);
			std::uint32_t list1Size = list1.Size();
			T list1Front = list1.Front();
			T list1Back = list1.Back();
			Assert::AreEqual(list1Size, list2.Size());
			Assert::AreEqual(list1Front, list2.Front());
			Assert::AreEqual(list1Back, list2.Back());
			list1.Clear();
			Assert::AreEqual(list1Size, list2.Size());
			Assert::AreEqual(list1Front, list2.Front());
			Assert::AreEqual(list1Back, list2.Back());
		}

		static void TestAssignmentOperatorSuccess(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list1;
			AnonymousEngine::SList<T> list2;
			list1.PushFront(value1);
			list1.PushFront(value2);

			// Verify that new memory has been allocated and lists are equivalent
			list2 = list1;
			std::uint32_t list1Size = list1.Size();
			T list1Front = list1.Front();
			T list1Back = list1.Back();
			Assert::AreEqual(list1Size, list2.Size());
			Assert::AreEqual(list1Front, list2.Front());
			Assert::AreEqual(list1Back, list2.Back());
			list1.Clear();
			Assert::AreEqual(list1Size, list2.Size());
			Assert::AreEqual(list1Front, list2.Front());
			Assert::AreEqual(list1Back, list2.Back());
		}

		static void TestAssignmentOperatorSelfCopyPrevention(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list1;
			list1.PushFront(value1);
			list1.PushFront(value2);

			// Verify that self assignment didn't do anything
			std::uint32_t list1Size = list1.Size();
			T list1Front = list1.Front();
			T list1Back = list1.Back();
			list1 = list1;
			Assert::AreEqual(list1Size, list1.Size());
			Assert::AreEqual(list1Front, list1.Front());
			Assert::AreEqual(list1Back, list1.Back());
		}

		static void TestPushFront(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			list.PushFront(value1);
			typename AnonymousEngine::SList<T>::Iterator it = list.PushFront(value2);
			Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
			Assert::AreEqual(value2, *it);
			Assert::AreEqual(value2, list.Front());
		}

		static void TestPopFrontRemovesItemAndUpdatesSize(const T& value1, const T& value2, const T& value3)
		{
			AnonymousEngine::SList<T> list;
			list.PushFront(value1);
			list.PushFront(value2);
			list.PushBack(value3);
			Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
			list.PopFront();
			Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
			Assert::AreEqual(value1, list.Front());
		}

		static void TestPushBack(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			list.PushBack(value1);
			typename AnonymousEngine::SList<T>::Iterator it = list.PushBack(value2);
			Assert::AreEqual(static_cast<std::uint32_t>(2), list.Size());
			Assert::AreEqual(value2, *it);
			Assert::AreEqual(value2, list.Back());
		}

		static void TestFrontReturnsItemInTheFront(const T& value1, const T& value2, const T& value3)
		{
			AnonymousEngine::SList<T> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			list.PushFront(value1);
			list.PushFront(value2);
			list.PushBack(value3);
			Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
			const AnonymousEngine::SList<T> constList(list);
			Assert::AreEqual(value2, list.Front());
			Assert::AreEqual(value2, constList.Front());
		}

		static void TestModifyingFrontValue(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			list.PushFront(value1);
			Assert::AreEqual(value1, list.Front());
			list.Front() = value2;
			Assert::AreEqual(value2, list.Front());
		}

		static void TestFrontThrowsExceptionWhenListIsEmpty()
		{
			AnonymousEngine::SList<T> list;
			const AnonymousEngine::SList<T> constList;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			Assert::ExpectException <std::domain_error>([&list]()
			{
				list.Front();
			}, L"Front on empty list did not throw an exception");
			Assert::ExpectException <std::domain_error>([&constList]()
			{
				constList.Front();
			}, L"Front on empty list did not throw an exception");
		}

		static void TestBackReturnsItemInTheBack(const T& value1, const T& value2, const T& value3)
		{
			AnonymousEngine::SList<T> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			list.PushBack(value2);
			list.PushBack(value1);
			list.PushFront(value3);
			Assert::AreEqual(static_cast<std::uint32_t>(3), list.Size());
			const AnonymousEngine::SList<T> constList(list);
			Assert::AreEqual(value1, list.Back());
			Assert::AreEqual(value1, constList.Back());
		}

		static void TestBackThrowsExceptionWhenListIsEmpty()
		{
			AnonymousEngine::SList<T> list;
			const AnonymousEngine::SList<T> constList;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			Assert::ExpectException <std::exception>([&list]()
			{
				list.Back();
			}, L"Back on empty list did not throw an exception");
			Assert::ExpectException <std::exception>([&constList]()
			{
				constList.Back();
			}, L"Front on empty list did not throw an exception");
		}

		static void TestModifyingBackValue(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			list.PushBack(value1);
			Assert::AreEqual(value1, list.Front());
			list.Back() = value2;
			Assert::AreEqual(value2, list.Back());
		}

		static void TestSizeMethod(const T& value)
		{
			AnonymousEngine::SList<T> list;
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
			list.PushBack(value);
			Assert::AreEqual(static_cast<std::uint32_t>(1), list.Size());
			list.Clear();
			Assert::AreEqual(static_cast<std::uint32_t>(0), list.Size());
		}

		static void TestEmptyMethod(const T& value)
		{
			AnonymousEngine::SList<T> list;
			Assert::IsTrue(list.IsEmpty());
			list.PushBack(value);
			Assert::IsFalse(list.IsEmpty());
			list.PopFront();
			Assert::IsTrue(list.IsEmpty());
		}

		static void TestClear(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list;
			Assert::IsTrue(list.IsEmpty());
			list.PushBack(value1);
			list.PushFront(value2);
			Assert::IsFalse(list.IsEmpty());
			list.Clear();
			Assert::IsTrue(list.IsEmpty());
		}

		static void TestBeginAndEnd(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list;
			Assert::AreEqual(list.begin(), list.end());
			list.PushFront(value1);
			Assert::IsFalse(list.begin() == list.end());
			list.PushBack(value2);
			Assert::AreEqual(list.Front(), *(list.begin()));
		}

		static void TestFind(const T& value1, const T& value2, const T& value3, const T& value4, const T& value5)
		{
			AnonymousEngine::SList<T> list;
			// test on empty list
			Assert::AreEqual(list.end(), list.Find(value1));

			// test on list with 1 element
			list.PushFront(value2);
			Assert::AreEqual(value2, *(list.Find(value2)));

			// test on list with multiple element
			list.PushBack(value3);
			list.PushBack(value4);
			Assert::AreEqual(*(list.Find(value3)), value3);
			Assert::AreNotEqual(list.end(), list.Find(value3));
			Assert::AreEqual(list.end(), list.Find(value5));
		}

		static void TestInsertAfter(const T& value1, const T& value2, const T& value3, const T& value4, const T& value5)
		{
			AnonymousEngine::SList<T> list;
			typename AnonymousEngine::SList<T>::Iterator it = list.InsertAfter(value1, list.begin());
			Assert::AreEqual(value1, *it);
			list.Clear();
			Assert::ExpectException<std::invalid_argument>([&list, &value1]()
			{
				typename AnonymousEngine::SList<T>::Iterator invalid;
				list.InsertAfter(value1, invalid);
			});

			// check when there is only 1 element
			T frontVal = value4;
			list.PushFront(frontVal);
			typename AnonymousEngine::SList<T>::Iterator it1 = list.InsertAfter(value2, list.begin());
			Assert::AreEqual(value2, *it1);
			Assert::AreEqual(value2, list.Back());

			// check when there are 2 and 3 elements
			T backVal = value5;
			list.PushBack(backVal);
			typename AnonymousEngine::SList<T>::Iterator it2 = list.InsertAfter(value3, list.Find(value2));
			Assert::AreEqual(value3, *it2);
			Assert::AreEqual(frontVal, *(list.begin()));

			typename AnonymousEngine::SList<T>::Iterator it3 = list.begin();
			Assert::AreEqual(value2, *(++it3));
			Assert::AreEqual(value3, *(++it3));
			Assert::AreEqual(backVal, *(++it3));
		}

		static void TestRemove(const T& value1, const T& value2, const T& value3, const T& value4)
		{
			AnonymousEngine::SList<T> list1;
			// check remove on empty list
			T frontVal = value1;
			Assert::IsFalse(list1.Remove(frontVal));
			Assert::IsTrue(list1.IsEmpty());

			// check on single item list
			list1.PushFront(frontVal);
			Assert::IsFalse(list1.Remove(value4));
			Assert::IsTrue(list1.Remove(frontVal));
			Assert::IsTrue(list1.IsEmpty());

			// check on 2 items list
			list1.PushFront(value3);
			list1.PushBack(value2);
			Assert::IsTrue(list1.Remove(value2));
			Assert::AreNotEqual(value2, list1.Back());
			Assert::AreEqual(static_cast<std::uint32_t>(1), list1.Size());

			// delete middle element from 3 element list
			AnonymousEngine::SList<T> list2;
			list2.PushFront(frontVal);
			T backVal = value4;
			list2.PushBack(value3);
			list2.PushBack(backVal);
			Assert::AreEqual(static_cast<std::uint32_t>(3), list2.Size());
			Assert::IsTrue(list2.Remove(value3));
			Assert::AreEqual(static_cast<std::uint32_t>(2), list2.Size());
			Assert::AreEqual(frontVal, list2.Front());
			Assert::AreEqual(backVal, list2.Back());

			// delete final element from 3 element list
			list2.InsertAfter(value3, list2.begin());
			Assert::AreEqual(static_cast<std::uint32_t>(3), list2.Size());
			Assert::IsTrue(list2.Remove(backVal));
			Assert::AreEqual(value3, list2.Back());
		}
	};
}