#pragma once

#include "CppUnitTestAssert.h"
#include "Datum.h"

namespace UnitTestLibraryDesktop
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	typedef AnonymousEngine::Datum Datum;
	typedef AnonymousEngine::Datum::DatumType DatumType;

	template <typename T>
	class DatumTestTemplate
	{
	public:
		static void TestDefaultConstructor(DatumType type)
		{
			Datum d(type);
			Assert::AreEqual(d.Type(), type);
			Assert::AreEqual(d.Size(), 0U);
		}
	};
}
