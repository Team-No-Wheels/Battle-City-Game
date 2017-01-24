#pragma once

#include "Foo.h"
#include "CppUnitTestAssert.h"
#include "SList.h"


namespace UnitTestLibraryDesktop
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	template <typename T>
	class SListIteratorTestTemplate
	{
	public:
		static void TestIteration(const T& value1, const T& value2, const T& value3)
		{
			AnonymousEngine::SList<T> list;
			list.PushBack(value1);
			list.PushBack(value2);
			list.PushBack(value3);
			
			auto it = list.begin();
			Assert::AreEqual(value1, *it++);
			Assert::AreEqual(value2, *it++);
			Assert::AreEqual(value3, *it++);
		}

		static void TestCopyConstructor(const T& value)
		{
			AnonymousEngine::SList<T> list;
			list.PushFront(value);
			auto iterator1 = list.begin();
			auto iterator2 = iterator1;
			Assert::AreEqual(*iterator1, *iterator2);
			Assert::AreEqual(iterator1, iterator2);
		}

		static void TestAssignmentOperator(const T& value)
		{
			AnonymousEngine::SList<T> list;
			list.PushFront(value);
			auto iterator1 = list.begin();
			typename AnonymousEngine::SList<T>::Iterator iterator2;
			iterator2 = iterator1;
			Assert::AreEqual(*iterator1, *iterator2);
			Assert::AreEqual(iterator1, iterator2);
		}

		static void TestPostAndPreIncrementOperators(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list;
			list.PushFront(value2);
			list.PushFront(value1);
			//test post increment
			auto iterator = list.begin();
			Assert::AreEqual(value1, list.Front());
			Assert::AreEqual(value1, *iterator);
			auto it = iterator++;
			Assert::AreEqual(value1, *it);
			Assert::AreEqual(value2, *iterator);
			// test pre increment
			iterator = list.begin();
			it = ++iterator;
			Assert::AreEqual(value2, *iterator);
			Assert::AreEqual(value2, list.Back());
		}

		static void TestIncrementOperatorsThrowsException(const T& value)
		{
			AnonymousEngine::SList<T> list;
			list.PushFront(value);
			auto iterator = list.end();
			Assert::AreEqual(value, list.Front());
			Assert::ExpectException<std::out_of_range>([&iterator]()
			{
				++iterator;
			});
			Assert::ExpectException<std::out_of_range>([&iterator]()
			{
				iterator++;
			});
		}

		static void TestDereferenceOperator(const T& value1, const T& value2)
		{
			// Test for non const version
			AnonymousEngine::SList<T> list1;
			Assert::ExpectException<std::domain_error>([&list1]()
			{
				*(list1.begin());
			});
			list1.PushFront(value1);
			Assert::AreEqual(value1, *(list1.begin()));
			list1.PushFront(value2);
			Assert::AreEqual(value2, *(list1.begin()));
			// Test for const version
			const typename AnonymousEngine::SList<T>::Iterator constIt(list1.begin());
			Assert::AreEqual(value2, *constIt);
			Assert::ExpectException<std::domain_error>([&list1]()
			{
				const typename AnonymousEngine::SList<T>::Iterator it;
				*it;
			});
		}

		static void TestEqualAndNotEqualOperators(const T& value1, const T& value2)
		{
			AnonymousEngine::SList<T> list1;
			AnonymousEngine::SList<T> list2;
			list1.PushFront(value1);
			list2.PushFront(value2);
			//equals operator
			Assert::AreEqual(list1.begin(), list1.begin());
			Assert::AreEqual(list1.end(), list1.end());
			Assert::AreNotEqual(list1.begin(), list2.begin());
			Assert::AreNotEqual(list1.end(), list2.end());
			//not equals operator
			Assert::AreEqual(list1.begin(), list1.begin());
			Assert::AreEqual(list1.end(), list1.end());
			Assert::AreNotEqual(list1.begin(), list2.begin());
			Assert::AreNotEqual(list1.end(), list2.end());
			typename AnonymousEngine::SList<T>::Iterator it1;
			typename AnonymousEngine::SList<T>::Iterator it2;
			Assert::AreEqual(it1, it2);
			Assert::AreEqual(it1, it2);
		}
	};
}
