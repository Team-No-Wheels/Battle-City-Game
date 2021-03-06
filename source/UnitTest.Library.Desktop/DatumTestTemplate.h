#pragma once

#include "CppUnitTestAssert.h"
#include "Datum.h"

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
			d = const_cast<T&>(value1);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			d = const_cast<T&>(value2);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			Assert::ExpectException<std::invalid_argument>([&d, &anotherType] { d.SetType(anotherType); });
		}

		static void TestGet(const T& value1, const T& value2)
		{
			Datum d;
			d = const_cast<T&>(value1);
			Assert::IsTrue(value1 == d.Get<T>());
			d = const_cast<T&>(value2);
			Assert::IsTrue(value2 == d.Get<T>());
			d.PushBack(const_cast<T&>(value1));
			Assert::AreEqual(2U, d.Size());
			Assert::IsTrue(value2 == d.Get<T>());
			Assert::IsTrue(value1 == d.Get<T>(1U));
		}

		static void TestCopyConstructor(const T& value1, const T& value2)
		{
			Datum* d1 = new Datum();
			*d1 = const_cast<T&>(value1);
			d1->PushBack(const_cast<T&>(value2));
			Datum d2(*d1);
			Assert::IsTrue(*d1 == d2);
			Assert::AreEqual(d1->Size(), d2.Size());
			Assert::AreEqual(d1->Type(), d2.Type());
			delete d1;
			Assert::IsTrue(value1 == d2.Get<T>());
			Assert::IsTrue(value2 == d2.Get<T>(1U));
		}

		static void TestAssignmentOperator(const T& value1, const T& value2)
		{
			Datum* d1 = new Datum();
			*d1 = const_cast<T&>(value1);
			d1->PushBack(const_cast<T&>(value2));
			Datum d2;
			d2 = const_cast<T&>(value2);
			Assert::IsFalse(*d1 == d2);
			Assert::IsTrue(value2 == d2.Get<T>());
			d2 = *d1;
			Assert::IsTrue(*d1 == d2);
			Assert::AreEqual(d1->Size(), d2.Size());
			Assert::AreEqual(d1->Type(), d2.Type());
			delete d1;
			Assert::IsTrue(value1 == d2.Get<T>());
			Assert::IsTrue(value2 == d2.Get<T>(1U));
		}

		static void TestMoveConstructor(const T& value1, const T& value2)
		{
			Datum* d1 = new Datum();
			(*d1) = const_cast<T&>(value1);
			d1->PushBack(const_cast<T&>(value2));
			std::uint32_t size = d1->Size();
			DatumType type = d1->Type();
			Datum d2(std::move(*d1));
			delete d1;

			Assert::IsTrue(value1 == d2.Get<T>());
			Assert::IsTrue(value2 == d2.Get<T>(1U));
			Assert::AreEqual(size, d2.Size());
			Assert::AreEqual(type, d2.Type());
		}

		static void TestMoveAssignmentOperator(const T& value1, const T& value2)
		{
			Datum* d1 = new Datum();
			(*d1) = const_cast<T&>(value1);
			d1->PushBack(const_cast<T&>(value2));
			std::uint32_t size = d1->Size();
			DatumType type = d1->Type();
			Datum d2;
			d2.PushBack(const_cast<T&>(value2));
			d2 = std::move(*d1);
			delete d1;

			Assert::IsTrue(value1 == d2.Get<T>());
			Assert::IsTrue(value2 == d2.Get<T>(1U));
			Assert::AreEqual(size, d2.Size());
			Assert::AreEqual(type, d2.Type());
		}

		static void TestConstantGet(const T& value1)
		{
			Datum d1;
			d1 = const_cast<T&>(value1);
			const Datum d2(d1);
			Assert::IsTrue(value1 == d2.Get<T>());
			Assert::AreEqual(1U, d2.Size());
		}

		static void TestSet(const DatumType type, const T& value1, const T& value2, const DatumType anotherType)
		{
			Datum d;
			d = const_cast<T&>(value1);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			d.Set(const_cast<T&>(value2));
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			Assert::ExpectException<std::invalid_argument>([&d, &anotherType] { d.SetType(anotherType); });
			d.Set(const_cast<T&>(value1));
			Assert::AreEqual(1U, d.Size());
			Assert::ExpectException<std::out_of_range>([&d, &value2] { d.Set(const_cast<T&>(value2), 1); });
			d.PushBack(const_cast<T&>(value1));
			Assert::AreEqual(2U, d.Size());
			Assert::IsTrue(value1 == d.Get<T>());
			Assert::IsTrue(value1 == d.Get<T>(1U));
			d.Set(const_cast<T&>(value2), 1U);
			Assert::IsTrue(value1 == d.Get<T>());
			Assert::IsTrue(value2 == d.Get<T>(1U));
			Assert::AreEqual(2U, d.Size());
		}

		static void TestPushBack(const DatumType type, const T& value1, const T& value2)
		{
			Datum d;
			d.PushBack(const_cast<T&>(value1));
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			d = const_cast<T&>(value1);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(1U, d.Size());
			d.PushBack(const_cast<T&>(value2));
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(2U, d.Size());
			Assert::IsTrue(value1 == d.Get<T>(0));
			Assert::IsTrue(value2 == d.Get<T>(1));
		}

		static void TestResize(const DatumType type, const T& value1, const T& value2)
		{
			Datum d;
			d.PushBack(const_cast<T&>(value1));
			d.PushBack(const_cast<T&>(value2));
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(2U, d.Size());
			d.Resize(3U);
			Assert::AreEqual(3U, d.Size());
			d.Set(const_cast<T&>(value1), 2U);
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
			d.PushBack(const_cast<T&>(value1));
			d.PushBack(const_cast<T&>(value2));
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
			d1 = const_cast<T&>(value1);
			Datum d2;
			d2 = const_cast<T&>(value2);
			Assert::IsTrue(d1 == value1);
			Assert::IsTrue(d2 == value2);
			Assert::IsFalse(d2 == value1);
			Assert::IsFalse(d1 == value2);
			Assert::IsFalse(d1 == d2);
			d2 = const_cast<T&>(value1);
			Assert::IsTrue(d2 == d1);
			d2.PushBack(const_cast<T&>(value1));
			Assert::IsFalse(d2 == d1);
			Assert::IsFalse(d2 == value1);
			Assert::IsFalse(d2 == value2);
		}

		static void TestNotEqualsOperator(const T& value1, const T& value2)
		{
			Datum d1;
			d1 = const_cast<T&>(value1);
			Datum d2;
			d2 = const_cast<T&>(value2);
			Assert::IsFalse(d1 != value1);
			Assert::IsFalse(d2 != value2);
			Assert::IsTrue(d2 != value1);
			Assert::IsTrue(d1 != value2);
			d2 = const_cast<T&>(value1);
			Assert::IsFalse(d2 != d1);
			d2.PushBack(const_cast<T&>(value1));
			Assert::IsTrue(d2 != d1);
			Assert::IsTrue(d2 != value1);
			Assert::IsTrue(d2 != value2);
		}

		static void TestSetStorage(const DatumType type, const T& value1, const T& value2, const DatumType anotherType)
		{
			T extValue1 = value1;
			T extValue2 = value2;

			Datum dFail;
			dFail.SetType(anotherType);
			Assert::ExpectException<std::invalid_argument>([&dFail, &extValue1] { dFail.SetStorage(&extValue1, 1U); });
			
			Datum d;
			d.SetType(type);
			Assert::IsFalse(d.IsExternal());
			d.SetStorage(&extValue1, 1U);
			Assert::IsTrue(d.IsExternal());
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
			Assert::AreEqual(2U, d1.Size());
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
