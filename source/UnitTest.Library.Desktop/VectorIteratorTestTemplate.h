#pragma once

#include "CppUnitTestAssert.h"
#include "Vector.h"


namespace UnitTestLibraryDesktop
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	template <typename T>
	class VectorIteratorTestTemplate
	{
	public:
		static void TestDerefenceOperator(const T& value)
		{
			typename AnonymousEngine::Vector<T>::Iterator iterator;
			Assert::ExpectException<std::out_of_range>([&iterator] { *iterator; });
			AnonymousEngine::Vector<T> vector;
			vector.PushBack(value);
			Assert::AreEqual(value, *vector.begin());
			Assert::AreEqual(value, *vector.IteratorAt(0));
			Assert::ExpectException<std::out_of_range>([&vector] { *vector.end(); });
		}

		static void TestPreIncrementOperator(const T& value)
		{
			typename AnonymousEngine::Vector<T>::Iterator iterator;
			Assert::ExpectException<std::out_of_range>([&iterator] { ++iterator; });
			AnonymousEngine::Vector<T> vector;
			vector.PushBack(value);
			Assert::AreNotEqual(vector.begin(), vector.end());
			Assert::AreEqual(vector.end(), ++vector.begin());
			Assert::ExpectException<std::out_of_range>([&vector] { ++vector.end(); });

			Assert::IsTrue(vector.end() == vector.begin().end());
			AnonymousEngine::Vector<T>::Iterator uninitializedIt;
			Assert::IsTrue(uninitializedIt == uninitializedIt.end());
		}

		static void TestPostIncrementOperator(const T& value1, const T& value2)
		{
			typename AnonymousEngine::Vector<T>::Iterator iterator;
			Assert::ExpectException<std::out_of_range>([&iterator] { iterator++; });
			AnonymousEngine::Vector<T> vector;
			vector.PushBack(value1);
			vector.PushBack(value2);
			Assert::AreNotEqual(vector.begin(), vector.end());
			iterator = vector.begin();
			Assert::AreEqual(*vector.begin(), *(iterator++));
			Assert::AreNotEqual(*vector.begin(), *iterator);
			Assert::AreNotEqual(vector.end(), iterator);
			Assert::ExpectException<std::out_of_range>([&vector] { vector.end()++; });
		}

		static void TestEqualityOperators(const T& value)
		{
			typename AnonymousEngine::Vector<T>::Iterator iterator;
			AnonymousEngine::Vector<T> vector;
			Assert::IsTrue(vector.begin() == vector.end());
			vector.PushBack(value);
			Assert::IsTrue(vector.begin() != vector.end());
			Assert::IsTrue(iterator != vector.end());
		}
	};
}
