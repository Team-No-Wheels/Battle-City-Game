#pragma once

#include "CppUnitTestAssert.h"
#include "Vector.h"
#include "CapacityStrategy.h"
#include "DefaultVectorCapacityStrategy.h"

namespace UnitTestLibraryDesktop
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	class TestCapacityStrategy : public AnonymousEngine::CapacityStrategy
	{
	public:
		TestCapacityStrategy() = default;
		~TestCapacityStrategy() = default;

		inline std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity) const override
		{
			if (capacity == 0)
			{
				return 2;
			}
			else
			{
				return size;
			}
		}
	};

	template <typename T>
	class VectorTestTemplate
	{
	public:
		static void TestDefaultConstructor()
		{
			AnonymousEngine::Vector<T> vector;
			AnonymousEngine::DefaultVectorCapacityStrategy strategy;
			Assert::AreEqual(strategy(0, 0), vector.Capacity());
			Assert::AreEqual(0U, vector.Size());
		}

		static void TestInitializerList(const T& value1, const T& value2, const T& value3)
		{
			AnonymousEngine::Vector<T> vector{value1, value2, value3};
			Assert::AreEqual(3U, vector.Size());
		}

		static void TestCopyConstructor(const T& value1, const T& value2, const T& value3, const T& value4)
		{
			AnonymousEngine::Vector<T> vector1;
			vector1.PushBack(value1);
			vector1.PushBack(value2);
			AnonymousEngine::Vector<T> vector2(vector1);
			Assert::AreEqual(vector1.Capacity(), vector2.Capacity());
			Assert::AreEqual(vector1.Size(), vector2.Size());
			vector1.PushBack(value3);
			vector1.PushBack(value4);
			AnonymousEngine::Vector<T> vector3(vector1);
			Assert::AreNotEqual(vector1.Capacity(), vector2.Capacity());
			Assert::AreNotEqual(vector1.Size(), vector2.Size());
			Assert::AreEqual(vector1.Capacity(), vector3.Capacity());
			Assert::AreEqual(vector1.Size(), vector3.Size());
		}

		static void TestAssignmentOperator(const T& value1, const T& value2, const T& value3, const T& value4)
		{
			AnonymousEngine::Vector<T> vector1;
			AnonymousEngine::Vector<T> vector2;
			vector1.PushBack(value1);
			vector1.PushBack(value2);
			vector2 = vector1;
			Assert::AreEqual(vector1.Capacity(), vector2.Capacity());
			Assert::AreEqual(vector1.Size(), vector2.Size());
			vector1.PushBack(value3);
			vector1.PushBack(value4);
			AnonymousEngine::Vector<T> vector3(vector1);
			Assert::AreNotEqual(vector1.Capacity(), vector2.Capacity());
			Assert::AreNotEqual(vector1.Size(), vector2.Size());
			Assert::AreEqual(vector1.Capacity(), vector3.Capacity());
			Assert::AreEqual(vector1.Size(), vector3.Size());
		}

		static void TestMoveConstructor(const T& value1, const T& value2, const T& value3, const T& value4)
		{
			AnonymousEngine::Vector<T>* vector1 = new AnonymousEngine::Vector<T>();
			vector1->PushBack(value1);
			vector1->PushBack(value2);
			std::uint32_t size = vector1->Size();
			std::uint32_t capacity = vector1->Capacity();
			AnonymousEngine::Vector<T> vector2 = std::move(*vector1);
			delete vector1;

			Assert::AreEqual(capacity, vector2.Capacity());
			Assert::AreEqual(size, vector2.Size());
			vector2.PushBack(value3);
			vector2.PushBack(value4);
			Assert::AreEqual(size + 2U, vector2.Size());
		}

		static void TestMoveAssignmentOperator(const T& value1, const T& value2, const T& value3, const T& value4)
		{
			AnonymousEngine::Vector<T>* vector1 = new AnonymousEngine::Vector<T>();
			vector1->PushBack(value1);
			vector1->PushBack(value2);
			std::uint32_t size = vector1->Size();
			std::uint32_t capacity = vector1->Capacity();
			AnonymousEngine::Vector<T> vector2;

			vector2.PushBack(value3);
			Assert::AreEqual(1U, vector2.Size());
			vector2 = std::move(*vector1);
			delete vector1;

			Assert::AreEqual(capacity, vector2.Capacity());
			Assert::AreEqual(size, vector2.Size());
			vector2.PushBack(value4);
			Assert::AreEqual(size + 1U, vector2.Size());
		}

		static void TestEmpty(const T& value)
		{
			AnonymousEngine::Vector<T> vector;
			AnonymousEngine::DefaultVectorCapacityStrategy strategy;
			Assert::AreEqual(0U, vector.Size());
			Assert::AreEqual(strategy(0, 0), vector.Capacity());
			Assert::IsTrue(vector.IsEmpty());
			vector.PushBack(value);
			Assert::IsFalse(vector.IsEmpty());
		}

		static void TestPushBack(const T& value1, const T& value2)
		{
			AnonymousEngine::Vector<T> vector;
			AnonymousEngine::DefaultVectorCapacityStrategy strategy;
			Assert::AreEqual(0U, vector.Size());
			Assert::AreEqual(strategy(0, 0), vector.Capacity());
			Assert::IsTrue(vector.IsEmpty());
			vector.PushBack(value1);
			Assert::AreEqual(1U, vector.Size());
			Assert::IsFalse(vector.IsEmpty());
			vector.PushBack(value2);
			Assert::AreEqual(2U, vector.Size());
			Assert::IsFalse(vector.IsEmpty());
		}

		static void TestPushBackVector(const T& value1, const T& value2, const T& value3)
		{
			AnonymousEngine::Vector<T> vector1;
			AnonymousEngine::Vector<T> vector2;
			AnonymousEngine::DefaultVectorCapacityStrategy strategy;
			vector1.PushBack(value1);
			Assert::AreEqual(1U, vector1.Size());
			Assert::IsFalse(vector1.IsEmpty());
			vector2.PushBack(value2);
			vector2.PushBack(value3);
			Assert::AreEqual(2U, vector2.Size());
			Assert::IsFalse(vector2.IsEmpty());
			vector1.PushBack(vector2);
			Assert::AreEqual(3U, vector1.Size());
			Assert::AreEqual(value1, vector1.Front());
			Assert::AreEqual(value3, vector1.Back());
		}

		static void TestPopBack(const T& value1, const T& value2)
		{
			AnonymousEngine::Vector<T> vector;
			vector.PushBack(value1);
			vector.PushBack(value2);
			Assert::AreEqual(2U, vector.Size());
			Assert::IsFalse(vector.IsEmpty());
			Assert::IsTrue(vector.PopBack());
			Assert::AreEqual(1U, vector.Size());
			Assert::IsTrue(vector.PopBack());
			Assert::AreEqual(0U, vector.Size());
			Assert::IsTrue(vector.IsEmpty());
			Assert::IsFalse(vector.PopBack());
		}

		static void TestFront(const T& value1, const T& value2)
		{
			AnonymousEngine::Vector<T> vector;
			Assert::ExpectException<std::out_of_range>([&vector] { vector.Front(); });
			vector.PushBack(value1);
			Assert::AreEqual(value1, vector.Front());
			vector.PushBack(value2);
			Assert::AreEqual(value1, vector.Front());
			vector.PopBack();
			Assert::AreEqual(value1, vector.Front());
			Assert::AreEqual(value1, const_cast<const AnonymousEngine::Vector<T>&>(vector).Front());
			vector.Front() = value2;
			Assert::AreEqual(value2, vector.Front());
			vector.PopBack();
			Assert::ExpectException<std::out_of_range>([&vector] { vector.Front(); });
		}

		static void TestBack(const T& value1, const T& value2)
		{
			AnonymousEngine::Vector<T> vector;
			Assert::ExpectException<std::out_of_range>([&vector] { vector.Back(); });
			vector.PushBack(value1);
			Assert::AreEqual(value1, vector.Back());
			vector.PushBack(value2);
			Assert::AreEqual(value2, vector.Back());
			vector.PopBack();
			Assert::AreEqual(value1, vector.Back());
			Assert::AreEqual(value1, const_cast<const AnonymousEngine::Vector<T>&>(vector).Back());
			vector.Back() = value2;
			Assert::AreEqual(value2, vector.Back());
			vector.PopBack();
			Assert::ExpectException<std::out_of_range>([&vector] { vector.Back(); });
		}

		static void TestClear(const T& value)
		{
			AnonymousEngine::Vector<T> vector;
			AnonymousEngine::DefaultVectorCapacityStrategy strategy;
			vector.PushBack(value);
			vector.PushBack(value);
			vector.PushBack(value);
			std::uint32_t newCapacity = strategy(vector.Size(), vector.Capacity()) + vector.Capacity();
			vector.PushBack(value);
			Assert::AreEqual(4U, vector.Size());
			Assert::AreEqual(newCapacity, vector.Capacity());
			vector.Clear();
			Assert::AreEqual(0U, vector.Capacity());
			Assert::IsTrue(vector.IsEmpty());
		}

		static void TestReserve(const std::uint32_t capacity, const T& value1, const T& value2, const T& value3, const T& value4)
		{
			AnonymousEngine::Vector<T> vector;
			AnonymousEngine::DefaultVectorCapacityStrategy strategy;
			Assert::AreEqual(strategy(0, 0), vector.Capacity());
			vector.PushBack(value1);
			vector.PushBack(value2);
			vector.PushBack(value3);
			Assert::AreEqual(strategy(0, 0), vector.Capacity());
			std::uint32_t newCapacity = strategy(vector.Size(), vector.Capacity()) + vector.Capacity();
			vector.PushBack(value4);
			Assert::AreEqual(4U, vector.Size());
			Assert::AreEqual(newCapacity, vector.Capacity());
			Assert::AreEqual(value1, vector.Front());
			Assert::AreEqual(value4, vector.Back());
		}

		static void TestIndexOfOperator(const T& value1, const T& value2)
		{
			AnonymousEngine::Vector<T> vector;
			vector.PushBack(value1);
			vector.PushBack(value2);
			Assert::AreEqual(value1, vector[0]);
			Assert::AreEqual(value2, vector[1]);
			Assert::ExpectException<std::out_of_range>([&vector] { vector[vector.Size()]; });
			vector[1] = value1;
			Assert::AreEqual(value1, const_cast<const AnonymousEngine::Vector<T>&>(vector)[1]);
		}

		static void TestEqualityOperators(const T& value1, const T& value2)
		{
			AnonymousEngine::Vector<T> vector1;
			AnonymousEngine::Vector<T> vector2;
			Assert::IsTrue(vector1 == vector2);
			Assert::IsFalse(vector1 != vector2);
			vector1.PushBack(value1);
			Assert::IsFalse(vector1 == vector2);
			Assert::IsTrue(vector1 != vector2);
			vector1.PushBack(value2);
			Assert::IsFalse(vector1 == vector2);
			Assert::IsTrue(vector1 != vector2);
			vector2.PushBack(value1);
			Assert::IsFalse(vector1 == vector2);
			Assert::IsTrue(vector1 != vector2);
			vector2.PushBack(value2);
			Assert::IsTrue(vector1 == vector2);
			Assert::IsFalse(vector1 != vector2);
		}

		static void TestFind(const T& value1, const T& value2)
		{
			AnonymousEngine::Vector<T> vector;
			Assert::AreEqual(vector.end(), vector.Find(value1));
			vector.PushBack(value1);
			Assert::AreEqual(value1, *vector.Find(value1));
			Assert::AreEqual(vector.end(), vector.Find(value2));
			vector.PushBack(value2);
			Assert::AreEqual(value1, *vector.Find(value1));
			Assert::AreEqual(value2, *vector.Find(value2));
		}

		static void TestRemoveElement(const T& value1, const T& value2, const T& value3)
		{
			AnonymousEngine::Vector<T> vector;
			Assert::IsFalse(vector.Remove(value1));
			vector.PushBack(value1);
			Assert::IsTrue(vector.Remove(value1));
			Assert::AreEqual(0U, vector.Size());
			vector.PushBack(value1);
			Assert::IsFalse(vector.Remove(value2));
			Assert::AreEqual(1U, vector.Size());
			vector.PushBack(value2);
			Assert::AreEqual(2U, vector.Size());
			Assert::IsTrue(vector.Remove(value2));
			Assert::AreEqual(1U, vector.Size());
			vector.PushBack(value2);
			vector.PushBack(value3);
			Assert::AreEqual(3U, vector.Size());
			Assert::IsTrue(vector.Remove(value2));
			Assert::AreEqual(2U, vector.Size());
			Assert::AreEqual(value1, *vector.begin());
			Assert::AreEqual(value3, *(++vector.begin()));
		}

		static void TestRemoveElementRange(const T& value1, const T& value2, const T& value3, const T& value4)
		{
			AnonymousEngine::Vector<T> vector;
			vector.PushBack(value1);
			vector.PushBack(value2);
			vector.PushBack(value3);
			vector.PushBack(value4);
			typename AnonymousEngine::Vector<T>::Iterator it;
			Assert::ExpectException<std::invalid_argument>([&vector, &it] { vector.Remove(vector.begin(), it); });
			Assert::AreEqual(4U, vector.Size());
			Assert::IsFalse(vector.Remove(vector.begin(), vector.begin()));
			Assert::AreEqual(4U, vector.Size());
			it = vector.begin();
			Assert::AreEqual(value1, *(it++));
			Assert::AreEqual(value2, *(it++));
			Assert::AreEqual(value3, *(it++));
			Assert::AreEqual(value4, *(it++));
			Assert::AreEqual(vector.end(), it);
			typename AnonymousEngine::Vector<T>::Iterator first = ++vector.begin();
			typename AnonymousEngine::Vector<T>::Iterator last = first;
			++last;
			++last;
			Assert::IsTrue(vector.Remove(first, last));
			Assert::AreEqual(2U, vector.Size());
			it = vector.begin();
			Assert::AreEqual(value1, *(it++));
			Assert::AreEqual(value4, *(it++));
			Assert::AreEqual(vector.end(), it);
		}

		static void TestCustomIncrementStrategy(const T& value1, const T& value2, const T& value3)
		{
			AnonymousEngine::Vector<T> vector;
			Assert::AreEqual(0U, vector.Size());
			Assert::AreEqual(3U, vector.Capacity());
			vector.PushBack(value1);
			vector.PushBack(value2);
			vector.PushBack(value3);
			Assert::AreEqual(3U, vector.Size());
			Assert::AreEqual(3U, vector.Capacity());
			vector.Clear();
			TestCapacityStrategy strategy;
			vector.IncrementStrategy(&strategy);
			vector.PushBack(value1);
			vector.PushBack(value2);
			Assert::AreEqual(2U, vector.Size());
			Assert::AreEqual(2U, vector.Capacity());
			vector.PushBack(value3);
			Assert::AreEqual(3U, vector.Size());
			Assert::AreEqual(4U, vector.Capacity());
			vector.Clear();
			vector.IncrementStrategy(nullptr);
			Assert::AreEqual(0U, vector.Size());
			Assert::AreEqual(0U, vector.Capacity());
			vector.PushBack(value1);
			vector.PushBack(value2);
			vector.PushBack(value3);
			Assert::AreEqual(3U, vector.Size());
			Assert::AreEqual(3U, vector.Capacity());
		}
	};
}
