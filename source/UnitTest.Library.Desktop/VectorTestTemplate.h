#pragma once

#include "CppUnitTestAssert.h"
#include "Vector.h"


namespace UnitTestLibraryDesktop
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	template <typename T>
	class VectorTestTemplate
	{
	public:
		static void TestDefaultConstructor()
		{
			AnonymousEngine::Vector<T> vector;
			Assert::AreEqual(static_cast<std::uint32_t>(3), vector.Capacity());
		}
	};
}
