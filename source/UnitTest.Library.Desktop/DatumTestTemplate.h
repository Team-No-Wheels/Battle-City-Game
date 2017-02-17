#pragma once

#include "CppUnitTestAssert.h"
#include "Datum.h"
#include <cmath>

namespace UnitTestLibraryDesktop
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	typedef AnonymousEngine::Datum Datum;
	typedef AnonymousEngine::Datum::DatumType DatumType;
	typedef AnonymousEngine::RTTI RTTI;

	template <typename T>
	class DatumTestTemplate
	{
	public:
		static void TestAssignmentScalar(const DatumType type, const T& value1, const T& value2, const DatumType anotherType)
		{
			Datum d;
			d = value1;
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			d = value2;
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			Assert::ExpectException<std::invalid_argument>([&d, &anotherType] { d.SetType(anotherType); });
		}

		static void TestGet(const T& value1, const T& value2)
		{
			Datum d;
			d = value1;
			Assert::IsTrue(value1 == d.Get<T>());
			d = value2;
			Assert::IsTrue(value2 == d.Get<T>());
			d.PushBack(value1);
			Assert::AreEqual(2U, d.Size());
			Assert::IsTrue(value2 == d.Get<T>());
			Assert::IsTrue(value1 == d.Get<T>(1U));
		}

		static void TestCopyConstructor(const T& value1, const T& value2)
		{
			Datum d1;
			d1 = value1;
			d1.PushBack(value2);
			Datum d2(d1);
			Assert::IsTrue(d1 == d2);
			Assert::IsTrue(value1 == d2.Get<T>());
			Assert::IsTrue(value2 == d2.Get<T>(1U));
			Assert::AreEqual(d1.Size(), d2.Size());
			Assert::AreEqual(d1.Type(), d2.Type());
		}

		static void TestAssignmentOperator(const T& value1, const T& value2)
		{
			Datum d1;
			d1 = value1;
			d1.PushBack(value2);
			Datum d2;
			d2 = value2;
			Assert::IsFalse(d1 == d2);
			Assert::IsTrue(value2 == d2.Get<T>());
			d2 = d1;
			Assert::IsTrue(d1 == d2);
			Assert::IsTrue(value1 == d2.Get<T>());
			Assert::IsTrue(value2 == d2.Get<T>(1U));
			Assert::AreEqual(d1.Size(), d2.Size());
			Assert::AreEqual(d1.Type(), d2.Type());
		}

		static void TestConstantGet(const T& value1)
		{
			Datum d1;
			d1 = value1;
			Datum d2(d1);
			Assert::IsTrue(value1 == d2.Get<T>());
			Assert::AreEqual(1U, d2.Size());
		}

		static void TestSet(const DatumType type, const T& value1, const T& value2, const DatumType anotherType)
		{
			Datum d;
			d = value1;
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			d.Set(value2);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			Assert::ExpectException<std::invalid_argument>([&d, &anotherType] { d.SetType(anotherType); });
			d.Set(value1);
			Assert::AreEqual(1U, d.Size());
			Assert::ExpectException<std::out_of_range>([&d, &value2] { d.Set(value2, 1); });
			d.PushBack(value1);
			Assert::AreEqual(2U, d.Size());
			Assert::IsTrue(value1 == d.Get<T>());
			Assert::IsTrue(value1 == d.Get<T>(1U));
			d.Set(value2, 1U);
			Assert::IsTrue(value1 == d.Get<T>());
			Assert::IsTrue(value2 == d.Get<T>(1U));
			Assert::AreEqual(2U, d.Size());
		}

		static void TestPushBack(const DatumType type, const T& value1, const T& value2)
		{
			Datum d;
			d.PushBack(value1);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			d = value1;
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			d.PushBack(value2);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(2U, d.Size());
			Assert::IsTrue(value1 == d.Get<T>(0));
			Assert::IsTrue(value2 == d.Get<T>(1));
		}

		static void TestResize(const DatumType type, const T& value1, const T& value2)
		{
			Datum d;
			d.PushBack(value1);
			d.PushBack(value2);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(2U, d.Size());
			d.Resize(3U);
			Assert::AreEqual(3U, d.Size());
			d.Set(value1, 2U);
			Assert::IsTrue(value1 == d.Get<T>(0));
			Assert::IsTrue(value2 == d.Get<T>(1));
			Assert::IsTrue(value1 == d.Get<T>(2));
			d.Resize(2U);
			Assert::AreEqual(2U, d.Size());
			Assert::ExpectException<std::out_of_range>([&d] { d.Get<T>(2); });
			d.Resize(0U);
			Assert::AreEqual(0U, d.Size());
		}

		static void TestPopBack(const DatumType type, const T& value1, const T& value2)
		{
			Datum d;
			Assert::IsFalse(d.PopBack());
			d.PushBack(value1);
			d.PushBack(value2);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(2U, d.Size());
			Assert::IsTrue(value1 == d.Get<T>(0));
			Assert::IsTrue(value2 == d.Get<T>(1));
			Assert::IsTrue(d.PopBack());
			Assert::AreEqual(1U, d.Size());
			Assert::IsTrue(value1 == d.Get<T>(0));
			Assert::ExpectException<std::out_of_range>([&d] { d.Get<T>(1); });
			Assert::IsTrue(d.PopBack());
			Assert::AreEqual(0U, d.Size());
			Assert::IsFalse(d.PopBack());
		}

		static void TestEqualsOperator(const T& value1, const T& value2)
		{
			Datum d1;
			d1 = value1;
			Datum d2;
			d2 = value2;
			Assert::IsTrue(d1 == value1);
			Assert::IsTrue(d2 == value2);
			Assert::IsFalse(d2 == value1);
			Assert::IsFalse(d1 == value2);
			Assert::IsFalse(d1 == d2);
			d2 = value1;
			Assert::IsTrue(d2 == d1);
			d2.PushBack(value1);
			Assert::IsFalse(d2 == d1);
			Assert::IsFalse(d2 == value1);
			Assert::IsFalse(d2 == value2);
		}

		static void TestNotEqualsOperator(const T& value1, const T& value2)
		{
			Datum d1;
			d1 = value1;
			Datum d2;
			d2 = value2;
			Assert::IsFalse(d1 != value1);
			Assert::IsFalse(d2 != value2);
			Assert::IsTrue(d2 != value1);
			Assert::IsTrue(d1 != value2);
			d2 = value1;
			Assert::IsFalse(d2 != d1);
			d2.PushBack(value1);
			Assert::IsTrue(d2 != d1);
			Assert::IsTrue(d2 != value1);
			Assert::IsTrue(d2 != value2);
		}

		static void TestSetStorage(const DatumType type, const T& value1, const T& value2, const DatumType anotherType)
		{
			Datum d;
			T extValue1 = value1;
			T extValue2 = value2;
			Assert::ExpectException<std::invalid_argument>([&d, &extValue1] { d.SetStorage(&extValue1, 1U); });
			d.SetType(type);
			d.SetStorage(&extValue1, 1U);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			d = value2;
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			d.SetStorage(&extValue1, 1U);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			Assert::ExpectException<std::invalid_argument>([&d, &anotherType] { d.SetType(anotherType); });

			T extValues[] = {extValue1, extValue2};
			d.SetStorage(extValues, 2U);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(2U, d.Size());
			Assert::IsTrue(extValue1 == d.Get<T>());
			Assert::IsTrue(extValue2 == d.Get<T>(1U));
			Assert::ExpectException<std::runtime_error>([&d, &extValue2] { d.PushBack(extValue2); });
			Assert::ExpectException<std::runtime_error>([&d] { d.PopBack(); });
			Assert::ExpectException<std::runtime_error>([&d] { d.Resize(1U); });
			d.Set(extValue2);
			Assert::AreEqual(2U, d.Size());
			Assert::IsTrue(extValue2 == d.Get<T>());
			Assert::IsTrue(extValue2 == d.Get<T>(1U));

			Datum d1;
			d1 = value1;
			d1 = d;
			Assert::IsTrue(d == d1);
			d1.Clear();
			Assert::AreEqual(0U, d1.Size());
			d1 = value1;
			d = d1;
			Assert::AreEqual(1U, d.Size());
		}

		static void TestToAndFromString(const T& value1, const T& value2, const T& value3, const T& value4, std::function<bool(const T&, const T&)> compare)
		{
			Datum d1;
			d1 = value1;
			Datum d2;
			d2 = value2;
			Datum d3, d4;
			d3.SetType(d1.Type());
			d4.SetType(d2.Type());
			d3 = value3;
			d4 = value4;
			d3.SetFromString(d1.ToString());
			d4.SetFromString(d2.ToString());
			Assert::IsTrue(!compare(d1.Get<T>(), d2.Get<T>()));
			Assert::IsTrue(!compare(d3.Get<T>(), d4.Get<T>()));
			std::string d1Str = d1.ToString();
			std::string d2Str = d2.ToString();
			std::string d3Str = d3.ToString();
			std::string d4Str = d4.ToString();
			Assert::IsTrue(compare(d1.Get<T>(), d3.Get<T>()));
			Assert::IsTrue(compare(d2.Get<T>(), d4.Get<T>()));
		}
	};
}
