#pragma once

#include "CppUnitTestAssert.h"
#include <cstdint>
#include "HashMap.h"

namespace UnitTestLibraryDesktop
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	template <typename Tkey>
	class HashMapTestTemplate
	{
	public:
		static void TestDefaultConstructor()
		{
			AnonymousEngine::HashMap<Tkey, std::uint32_t> map;
			Assert::AreEqual(0U, map.Size());
		}
	};
}
