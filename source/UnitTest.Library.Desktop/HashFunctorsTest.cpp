#include "Pch.h"
#include <cstdint>
#include <cstring>
#include "Foo.h"
#include "TestClassHelper.h"
#include "HashFunctors.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnonymousEngine
{
	template <>
	class DefaultHashFunctor<UnitTestLibraryDesktop::Foo>
	{
	public:
		std::uint32_t operator()(const UnitTestLibraryDesktop::Foo& data) const
		{
			std::uint32_t intData = data.Data();
			return HashFunctions::SuperFastHash(reinterpret_cast<const int8_t*>(&intData), static_cast<std::uint32_t>(sizeof(intData)));
		}
	};

	template <>
	class DefaultHashFunctor<const UnitTestLibraryDesktop::Foo>
	{
	public:
		std::uint32_t operator()(const UnitTestLibraryDesktop::Foo& data) const
		{
			std::uint32_t intData = data.Data();
			return HashFunctions::SuperFastHash(reinterpret_cast<const int8_t*>(&intData), static_cast<std::uint32_t>(sizeof(intData)));
		}
	};
}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(HashFunctorsTest)
	{
	public:
		TEST_METHOD(TestHashFunctionWithInt)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			AnonymousEngine::DefaultHashFunctor<std::uint32_t> intFunctor;
			Assert::AreEqual(intFunctor(value1), intFunctor(value1));
			Assert::AreNotEqual(intFunctor(value1), intFunctor(value2));
		}

		TEST_METHOD(TestHashFunctionWithIntPointer)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = value1;
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			std::uint32_t* ptr1 = &value1;
			std::uint32_t* ptr2 = &value1;
			AnonymousEngine::DefaultHashFunctor<std::uint32_t*> intPtrFunctor;
			Assert::AreEqual(intPtrFunctor(ptr1), intPtrFunctor(ptr2));
			ptr2 = &value2;
			Assert::AreNotEqual(intPtrFunctor(ptr1), intPtrFunctor(ptr2));
			ptr2 = &value3;
			Assert::AreNotEqual(intPtrFunctor(ptr1), intPtrFunctor(ptr2));
		}

		TEST_METHOD(TestHashFunctionWithCharPointer)
		{
			const char* string1 = "Hello";
			const char* string2 = "Hello";
			const char* string3 = "Hello, World!";
			const char* string4 = "Foo";
			AnonymousEngine::DefaultHashFunctor<char*> charPtrFunctor;
			Assert::AreEqual(charPtrFunctor(string1), charPtrFunctor(string2));
			Assert::AreEqual(charPtrFunctor(string1), charPtrFunctor(string1));
			Assert::AreNotEqual(charPtrFunctor(string1), charPtrFunctor(string3));
			Assert::AreNotEqual(charPtrFunctor(string1), charPtrFunctor(string3));
			Assert::AreEqual(charPtrFunctor(string4), charPtrFunctor(string4));
			Assert::IsTrue(charPtrFunctor(nullptr) == 0U);
			AnonymousEngine::DefaultHashFunctor<const char*> constCharPtrFunctor;
			Assert::AreEqual(constCharPtrFunctor(string1), constCharPtrFunctor(string2));
			Assert::AreEqual(constCharPtrFunctor(string1), constCharPtrFunctor(string1));
			Assert::AreNotEqual(constCharPtrFunctor(string1), constCharPtrFunctor(string3));
			Assert::IsTrue(constCharPtrFunctor("") == 0U);
			Assert::IsTrue(constCharPtrFunctor(nullptr) == 0U);
		}

		TEST_METHOD(TestHashFunctionWithString)
		{
			std::string string1 = "Hello";
			std::string string2 = "Hello";
			std::string string3 = "Hello, World!";
			AnonymousEngine::DefaultHashFunctor<std::string> stringFunctor;
			Assert::AreEqual(stringFunctor(string1), stringFunctor(string2));
			Assert::AreEqual(stringFunctor(string1), stringFunctor(string1));
			Assert::AreNotEqual(stringFunctor(string1), stringFunctor(string3));
			AnonymousEngine::DefaultHashFunctor<const std::string> constStringFunctor;
			Assert::AreEqual(constStringFunctor(string1), constStringFunctor(string2));
			Assert::AreEqual(constStringFunctor(string1), constStringFunctor(string1));
			Assert::AreNotEqual(constStringFunctor(string1), constStringFunctor(string3));
		}

		TEST_METHOD(TestHashFunctionWithFoo)
		{
			Foo f1 = Foo(mHelper.GetRandomUInt32());
			Foo f2 = f1;
			Foo f3 = Foo(mHelper.GetRandomUInt32());
			AnonymousEngine::DefaultHashFunctor<Foo> fooFunctor;
			Assert::AreEqual(fooFunctor(f1), fooFunctor(f1));
			Assert::AreEqual(fooFunctor(f1), fooFunctor(f2));
			Assert::AreNotEqual(fooFunctor(f1), fooFunctor(f3));
		}

		TEST_CLASS_INITIALIZE(InitializeClass)
		{
			mHelper.BeginClass();
		}

		TEST_METHOD_INITIALIZE(Setup)
		{
			mHelper.Setup();
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			mHelper.Teardown();
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			mHelper.EndClass();
		}
	private:
		static TestClassHelper mHelper;
	};

	TestClassHelper HashFunctorsTest::mHelper;
}
