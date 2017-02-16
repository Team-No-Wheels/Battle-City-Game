#include "Pch.h"
#include "HashMapTestTemplate.h"
#include "TestClassHelper.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnonymousEngine
{
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
	TEST_CLASS(HashMapTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			HashMapTestTemplate<std::uint32_t>::TestDefaultConstructor();
			HashMapTestTemplate<std::uint32_t*>::TestDefaultConstructor();
			HashMapTestTemplate<const char*>::TestDefaultConstructor();
			HashMapTestTemplate<char*>::TestDefaultConstructor();
			HashMapTestTemplate<std::string>::TestDefaultConstructor();
			HashMapTestTemplate<const std::string>::TestDefaultConstructor();
			HashMapTestTemplate<Foo>::TestDefaultConstructor();
		}

		TEST_METHOD(TestInitializerListConstructor)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			HashMapTestTemplate<std::uint32_t>::TestInitializerListConstructor(value1, value2, value3);
			HashMapTestTemplate<std::uint32_t*>::TestInitializerListConstructor(&value1, &value2, &value3);
			std::string str1 = "hello1";
			std::string str2 = "hello2";
			std::string str3 = "hello3";
			HashMapTestTemplate<const char*>::TestInitializerListConstructor(str1.c_str(), str2.c_str(), str3.c_str());
			HashMapTestTemplate<char*>::TestInitializerListConstructor(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()), const_cast<char*>(str3.c_str()));
			HashMapTestTemplate<std::string>::TestInitializerListConstructor(str1, str2, str3);
			HashMapTestTemplate<const std::string>::TestInitializerListConstructor(str1, str2, str3);
			HashMapTestTemplate<Foo>::TestInitializerListConstructor(Foo(value1), Foo(value2), Foo(value3));
		}

		TEST_METHOD(TestCopyConstructor)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			HashMapTestTemplate<std::uint32_t>::TestCopyConstructor(value1, value2);
			HashMapTestTemplate<std::uint32_t*>::TestCopyConstructor(&value1, &value2);
			std::string str1 = "hello1";
			std::string str2 = "hello2";
			HashMapTestTemplate<const char*>::TestCopyConstructor(str1.c_str(), str2.c_str());
			HashMapTestTemplate<char*>::TestCopyConstructor(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()));
			HashMapTestTemplate<std::string>::TestCopyConstructor(str1, str2);
			HashMapTestTemplate<const std::string>::TestCopyConstructor(str1, str2);
			HashMapTestTemplate<Foo>::TestCopyConstructor(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::string str1 = "hello1";
			std::string str2 = "hello2";
			HashMapTestTemplate<std::uint32_t>::TestCopyConstructor(value1, value2);
			HashMapTestTemplate<std::uint32_t*>::TestCopyConstructor(&value1, &value2);
			HashMapTestTemplate<const char*>::TestCopyConstructor(str1.c_str(), str2.c_str());
			HashMapTestTemplate<char*>::TestCopyConstructor(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()));
			HashMapTestTemplate<std::string>::TestCopyConstructor(str1, str2);
			HashMapTestTemplate<const std::string>::TestCopyConstructor(str1, str2);
			HashMapTestTemplate<Foo>::TestCopyConstructor(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestFind)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			std::string str1 = "hello1";
			std::string str2 = "hello2";
			std::string str3 = "hello3";
			HashMapTestTemplate<std::uint32_t>::TestFind(value1, value2, value3);
			HashMapTestTemplate<std::uint32_t*>::TestFind(&value1, &value2, &value3);
			HashMapTestTemplate<const char*>::TestFind(str1.c_str(), str2.c_str(), str3.c_str());
			HashMapTestTemplate<char*>::TestFind(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()), const_cast<char*>(str3.c_str()));
			HashMapTestTemplate<std::string>::TestFind(str1, str2, str3);
			HashMapTestTemplate<const std::string>::TestFind(str1, str2, str3);
			HashMapTestTemplate<Foo>::TestFind(Foo(value1), Foo(value2), Foo(value3));
		}

		TEST_METHOD(TestInsert)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			std::string str1 = "hello1";
			std::string str2 = "hello2";
			std::string str3 = "hello3";
			HashMapTestTemplate<std::uint32_t>::TestInsert(value1, value2, value3);
			HashMapTestTemplate<std::uint32_t*>::TestInsert(&value1, &value2, &value3);
			HashMapTestTemplate<const char*>::TestInsert(str1.c_str(), str2.c_str(), str3.c_str());
			HashMapTestTemplate<char*>::TestInsert(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()), const_cast<char*>(str3.c_str()));
			HashMapTestTemplate<std::string>::TestInsert(str1, str2, str3);
			HashMapTestTemplate<const std::string>::TestInsert(str1, str2, str3);
			HashMapTestTemplate<Foo>::TestInsert(Foo(value1), Foo(value2), Foo(value3));
		}

		TEST_METHOD(TestDereferenceOperators)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			std::string str1 = "hello1";
			std::string str2 = "hello2";
			std::string str3 = "hello3";
			HashMapTestTemplate<std::uint32_t>::TestDereferenceOperators(value1, value2, value3);
			HashMapTestTemplate<std::uint32_t*>::TestDereferenceOperators(&value1, &value2, &value3);
			HashMapTestTemplate<const char*>::TestDereferenceOperators(str1.c_str(), str2.c_str(), str3.c_str());
			HashMapTestTemplate<char*>::TestDereferenceOperators(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()), const_cast<char*>(str3.c_str()));
			HashMapTestTemplate<std::string>::TestDereferenceOperators(str1, str2, str3);
			HashMapTestTemplate<const std::string>::TestDereferenceOperators(str1, str2, str3);
			HashMapTestTemplate<Foo>::TestDereferenceOperators(Foo(value1), Foo(value2), Foo(value3));
		}

		TEST_METHOD(TestIndexOfOperator)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			std::uint32_t value4 = mHelper.GetRandomUInt32();
			std::string str1 = "hello1";
			std::string str2 = "hello2";
			std::string str3 = "hello3";
			std::string str4 = "hello4";
			HashMapTestTemplate<std::uint32_t>::TestIndexOfOperator(value1, value2, value3, value4);
			HashMapTestTemplate<std::uint32_t*>::TestIndexOfOperator(&value1, &value2, &value3, &value4);
			HashMapTestTemplate<const char*>::TestIndexOfOperator(str1.c_str(), str2.c_str(), str3.c_str(), str4.c_str());
			HashMapTestTemplate<char*>::TestIndexOfOperator(const_cast<char*>(str1.c_str()), 
				const_cast<char*>(str2.c_str()), const_cast<char*>(str3.c_str()), const_cast<char*>(str4.c_str()));
			HashMapTestTemplate<std::string>::TestIndexOfOperator(str1, str2, str3, str4);
			HashMapTestTemplate<const std::string>::TestIndexOfOperator(str1, str2, str3, str4);
			HashMapTestTemplate<Foo>::TestIndexOfOperator(Foo(value1), Foo(value2), Foo(value3), Foo(value4));
		}

		TEST_METHOD(TestRemove)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			std::uint32_t value4 = mHelper.GetRandomUInt32();
			std::string str1 = "hello1";
			std::string str2 = "hello2";
			std::string str3 = "hello3";
			std::string str4 = "hello4";
			HashMapTestTemplate<std::uint32_t>::TestRemove(value1, value2, value3, value4);
			HashMapTestTemplate<std::uint32_t*>::TestRemove(&value1, &value2, &value3, &value4);
			HashMapTestTemplate<const char*>::TestRemove(str1.c_str(), str2.c_str(), str3.c_str(), str4.c_str());
			HashMapTestTemplate<char*>::TestRemove(const_cast<char*>(str1.c_str()),
				const_cast<char*>(str2.c_str()), const_cast<char*>(str3.c_str()), const_cast<char*>(str4.c_str()));
			HashMapTestTemplate<std::string>::TestRemove(str1, str2, str3, str4);
			HashMapTestTemplate<const std::string>::TestRemove(str1, str2, str3, str4);
			HashMapTestTemplate<Foo>::TestRemove(Foo(value1), Foo(value2), Foo(value3), Foo(value4));
		}

		TEST_METHOD(TestContainsKey)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			std::string str1 = "hello1";
			std::string str2 = "hello2";
			std::string str3 = "hello3";
			HashMapTestTemplate<std::uint32_t>::TestContainsKey(value1, value2, value3);
			HashMapTestTemplate<std::uint32_t*>::TestContainsKey(&value1, &value2, &value3);
			HashMapTestTemplate<const char*>::TestContainsKey(str1.c_str(), str2.c_str(), str3.c_str());
			HashMapTestTemplate<char*>::TestContainsKey(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()), const_cast<char*>(str3.c_str()));
			HashMapTestTemplate<std::string>::TestContainsKey(str1, str2, str3);
			HashMapTestTemplate<const std::string>::TestContainsKey(str1, str2, str3);
			HashMapTestTemplate<Foo>::TestContainsKey(Foo(value1), Foo(value2), Foo(value3));
		}

		TEST_METHOD(TestClear)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::string str1 = "hello1";
			std::string str2 = "hello2";
			HashMapTestTemplate<std::uint32_t>::TestClear(value1, value2);
			HashMapTestTemplate<std::uint32_t*>::TestClear(&value1, &value2);
			HashMapTestTemplate<const char*>::TestClear(str1.c_str(), str2.c_str());
			HashMapTestTemplate<char*>::TestClear(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()));
			HashMapTestTemplate<std::string>::TestClear(str1, str2);
			HashMapTestTemplate<const std::string>::TestClear(str1, str2);
			HashMapTestTemplate<Foo>::TestClear(Foo(value1), Foo(value2));
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

	TestClassHelper HashMapTest::mHelper;
}
