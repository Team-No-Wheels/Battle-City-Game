#include "Pch.h"
#include "HashMapTestTemplate.h"
#include "TestClassHelper.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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

		TEST_METHOD(TestCopyConstructor)
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

		TEST_METHOD(TestIndexOfOperator)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			/*std::string str1 = "hello1";
			std::string str2 = "hello2";
			std::string str3 = "hello3";*/
			HashMapTestTemplate<std::uint32_t>::TestIndexOfOperator(value1, value2, value3);
			/*HashMapTestTemplate<std::uint32_t*>::TestIndexOfOperator(&value1, &value2, &value3);
			HashMapTestTemplate<const char*>::TestIndexOfOperator(str1.c_str(), str2.c_str(), str3.c_str());
			HashMapTestTemplate<char*>::TestIndexOfOperator(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()), const_cast<char*>(str3.c_str()));
			HashMapTestTemplate<std::string>::TestIndexOfOperator(str1, str2, str3);
			HashMapTestTemplate<const std::string>::TestIndexOfOperator(str1, str2, str3);
			HashMapTestTemplate<Foo>::TestIndexOfOperator(Foo(value1), Foo(value2), Foo(value3));*/
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
