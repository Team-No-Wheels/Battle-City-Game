#include "Pch.h"
#include <cstdint>
#include <cstring>
#include "Foo.h"
#include "TestClassHelper.h"
#include "HashFunctors.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
			AnonymousEngine::DefaultHashFunctor<char*> charPtrFunctor;
			Assert::AreEqual(charPtrFunctor(string1), charPtrFunctor(string2));
			Assert::AreEqual(charPtrFunctor(string1), charPtrFunctor(string1));
			Assert::AreNotEqual(charPtrFunctor(string1), charPtrFunctor(string3));
			AnonymousEngine::DefaultHashFunctor<const char*> constCharPtrFunctor;
			Assert::AreEqual(constCharPtrFunctor(string1), constCharPtrFunctor(string2));
			Assert::AreEqual(constCharPtrFunctor(string1), constCharPtrFunctor(string1));
			Assert::AreNotEqual(constCharPtrFunctor(string1), constCharPtrFunctor(string3));
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
			AnonymousEngine::DefaultHashFunctor<std::uint32_t> intFunctor;
			Assert::AreEqual(fooFunctor(f1), fooFunctor(f1));
			Assert::AreNotEqual(fooFunctor(f1), fooFunctor(f2));
			std::uint32_t value1 = f1.Data();
			std::uint32_t value2 = f2.Data();
			Assert::AreEqual(intFunctor(value1), intFunctor(value2));
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
