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
	public:
		static void TestDefaultConstructor()
		{
			AnonymousEngine::HashMap<TKey, std::uint32_t> map;
			Assert::AreEqual(0U, map.Size());
		}

		static void TestCopyConstructor(const TKey& value1, const TKey& value2)
		{
			std::pair<TKey, std::uint32_t> pair1(value1, 1U);
			std::pair<TKey, std::uint32_t> pair2(value2, 2U);
			AnonymousEngine::HashMap<TKey, std::uint32_t> map1;
			map1.Insert(pair1);
			map1.Insert(pair2);
			Assert::AreEqual(2U, map1.Size());
			AnonymousEngine::HashMap<TKey, std::uint32_t> map2(map1);
			Assert::AreEqual(map1.Size(), map2.Size());
			Assert::IsTrue(*map1.begin() == *map2.begin());
		}

		static void TestAssignmentOperator(const TKey& value1, const TKey& value2)
		{
			std::pair<TKey, std::uint32_t> pair1(value1, 1U);
			std::pair<TKey, std::uint32_t> pair2(value2, 2U);
			AnonymousEngine::HashMap<TKey, std::uint32_t> map1;
			map1.Insert(pair1);
			map1.Insert(pair2);
			Assert::AreEqual(2U, map1.Size());
			AnonymousEngine::HashMap<TKey, std::uint32_t> map2;
			map2 = map1;
			Assert::AreEqual(map1.Size(), map2.Size());
			Assert::IsTrue(*map1.begin() == *map2.begin());
		}

		static void TestFind(const TKey& value1, const TKey& value2, const TKey& value3)
		{
			std::pair<TKey, std::uint32_t> pair1(value1, 1U);
			std::pair<TKey, std::uint32_t> pair2(value2, 2U);
			std::pair<TKey, std::uint32_t> pair3(value3, 3U);
			AnonymousEngine::HashMap<TKey, std::uint32_t> map;
			map.Insert(pair1);
			//map.Insert(pair2);
			//map.Insert(pair3);
			Assert::AreEqual(1U, map.Size());
			auto it = map.Find(value1);
			Assert::IsTrue(pair1 == *map.Find(value1));
			/*Assert::IsTrue(pair2 == *map.Find(value2));
			Assert::IsTrue(pair3 == *map.Find(value3));*/
		}

		static void TestInsert(const TKey& value1, const TKey& value2, const TKey& value3)
		{
			std::pair<TKey, std::uint32_t> pair1(value1, 1U);
			std::pair<TKey, std::uint32_t> pair2(value2, 2U);
			std::pair<TKey, std::uint32_t> pair3(value3, 3U);
			std::pair<TKey, std::uint32_t> pair(value2, 3U);
			AnonymousEngine::HashMap<TKey, std::uint32_t> map;
			map.Insert(pair1);
			map.Insert(pair2);
			typename AnonymousEngine::HashMap<TKey, std::uint32_t>::Iterator it = map.Insert(pair3);
			Assert::AreEqual(3U, map.Size());
			Assert::IsTrue(*it == *map.Insert(pair));
		}
	};
}
