#pragma once

#include "CppUnitTestAssert.h"
#include <cstdint>
#include "HashMap.h"

namespace UnitTestLibraryDesktop
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	template <typename TKey>
	class HashMapTestTemplate
	{
		typedef AnonymousEngine::HashMap<TKey, std::uint32_t> MapType;
		typedef typename AnonymousEngine::HashMap<TKey, std::uint32_t>::EntryType EntryType;
		typedef typename AnonymousEngine::HashMap<TKey, std::uint32_t>::Iterator IteratorType;
	public:
		static void TestDefaultConstructor()
		{
			MapType map;
			Assert::AreEqual(0U, map.Size());
		}

		static void TestCopyConstructor(const TKey& value1, const TKey& value2)
		{
			EntryType pair1(value1, 1U);
			EntryType pair2(value2, 2U);
			MapType map1;
			map1.Insert(pair1);
			map1.Insert(pair2);
			Assert::AreEqual(2U, map1.Size());
			MapType map2(map1);
			Assert::AreEqual(map1.Size(), map2.Size());
			Assert::IsTrue(*map1.begin() == *map2.begin());
		}

		static void TestAssignmentOperator(const TKey& value1, const TKey& value2)
		{
			EntryType pair1(value1, 1U);
			EntryType pair2(value2, 2U);
			MapType map1;
			map1.Insert(pair1);
			map1.Insert(pair2);
			Assert::AreEqual(2U, map1.Size());
			MapType map2;
			map2 = map1;
			Assert::AreEqual(map1.Size(), map2.Size());
			Assert::IsTrue(*map1.begin() == *map2.begin());
		}

		static void TestFind(const TKey& value1, const TKey& value2, const TKey& value3)
		{
			EntryType pair1(value1, 1U);
			EntryType pair2(value2, 2U);
			EntryType pair3(value3, 3U);
			MapType map;
			Assert::IsTrue(map.end() == map.Find(value1));
			map.Insert(pair1);
			map.Insert(pair2);
			Assert::IsTrue(map.end() != map.Find(value1));
			Assert::IsTrue(map.end() == map.Find(value3));
			map.Insert(pair3);
			Assert::AreEqual(3U, map.Size());
			Assert::IsTrue(pair1 == *map.Find(value1));
			Assert::IsTrue(pair2 == *map.Find(value2));
			Assert::IsTrue(pair3 == *map.Find(value3));
		}

		static void TestInsert(const TKey& value1, const TKey& value2, const TKey& value3)
		{
			EntryType pair1(value1, 1U);
			EntryType pair2(value2, 2U);
			EntryType pair3(value3, 3U);
			EntryType pair(value2, 3U);
			MapType map;
			map.Insert(pair1);
			IteratorType it = map.Insert(pair2);
			map.Insert(pair3);
			Assert::AreEqual(3U, map.Size());
			Assert::IsTrue(pair1 == *map.Find(value1));
			Assert::IsTrue(it == map.Insert(pair));
			Assert::IsTrue(*it == *map.Insert(pair));
		}

		static void TestDereferenceOperators(const TKey& value1, const TKey& value2, const TKey& value3)
		{
			EntryType pair1(value1, 1U);
			EntryType pair2(value2, 2U);
			EntryType pair3(value3, 3U);
			MapType map;
			map.Insert(pair1);
			map.Insert(pair2);
			map.Insert(pair3);
			Assert::AreEqual(3U, map.Size());
			Assert::IsTrue(pair1 == *map.Find(value1));
			Assert::IsTrue(pair2 == *map.Find(value2));
			Assert::IsTrue(pair3 == *map.Find(value3));
			Assert::IsTrue(pair1.second == map.Find(value1)->second);
			Assert::IsTrue(pair2.second == map.Find(value2)->second);
			Assert::IsTrue(pair3.second == map.Find(value3)->second);
		}

		static void TestIndexOfOperator(const TKey& value1, const TKey& value2, const TKey& value3, const TKey& value4)
		{
			EntryType pair1(value1, 1U);
			EntryType pair2(value2, 2U);
			EntryType pair3(value3, 3U);
			EntryType entry;
			MapType map1;
			map1.Insert(pair1);
			map1.Insert(pair2);
			Assert::AreEqual(1U, map1[value1]);
			Assert::AreEqual(2U, map1[value2]);
			Assert::AreEqual(entry.second, map1[value3]);
			map1[value3] = 3U;
			Assert::AreEqual(3U, map1[value3]);
			Assert::AreEqual(3U, map1.Size());
			const MapType map2(map1);
			Assert::AreEqual(3U, map2.Size());
			Assert::AreEqual(3U, map2[value3]);
			Assert::ExpectException<std::out_of_range>([&map2, &value4] { map2[value4]; });
		}

		static void TestRemove(const TKey& value1, const TKey& value2, const TKey& value3, const TKey& value4)
		{
			EntryType pair1(value1, 1U);
			EntryType pair2(value2, 2U);
			EntryType pair3(value3, 3U);
			MapType map;
			Assert::IsFalse(map.Remove(value4));
			map.Insert(pair1);
			map.Insert(pair2);
			map.Insert(pair3);
			Assert::AreEqual(3U, map.Size());
			Assert::IsFalse(map.Remove(value4));
			Assert::IsTrue(map.Remove(value2));
			Assert::IsTrue(map.Remove(value3));
			Assert::IsTrue(map.Remove(value1));
			Assert::IsFalse(map.Remove(value1));
		}

		static void TestContainsKey(const TKey& value1, const TKey& value2, const TKey& value3)
		{
			EntryType pair1(value1, 1U);
			EntryType pair2(value2, 2U);
			EntryType pair3(value3, 3U);
			MapType map;
			Assert::IsFalse(map.ContainsKey(value1));
			map.Insert(pair1);
			map.Insert(pair2);
			Assert::IsTrue(map.ContainsKey(value1));
			Assert::IsTrue(map.ContainsKey(value2));
			Assert::IsFalse(map.ContainsKey(value3));
			map.Insert(pair3);
			Assert::IsTrue(map.ContainsKey(value3));
		}

		static void TestClear(const TKey& value1, const TKey& value2)
		{
			EntryType pair1(value1, 1U);
			EntryType pair2(value2, 2U);
			MapType map;
			Assert::IsTrue(map.begin() == map.end());
			Assert::AreEqual(0U, map.Size());
			map.Insert(pair1);
			map.Insert(pair2);
			Assert::IsTrue(map.begin() != map.end());
			Assert::AreEqual(2U, map.Size());
			map.Clear();
			Assert::AreEqual(0U, map.Size());
			Assert::IsTrue(map.begin() == map.end());
		}
	};
}
