#include "Pch.h"
#include "Foo.h"
#include "VectorTestTemplate.h"
#include "TestClassHelper.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(VectorTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			VectorTestTemplate<std::uint32_t>::TestDefaultConstructor();
			VectorTestTemplate<std::uint32_t*>::TestDefaultConstructor();
			VectorTestTemplate<Foo>::TestDefaultConstructor();
		}

		TEST_METHOD(TestCopyConstructor)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			std::uint32_t value4 = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestCopyConstructor(value1, value2, value3, value4);
			VectorTestTemplate<std::uint32_t*>::TestCopyConstructor(&value1, &value2, &value3, &value4);
			VectorTestTemplate<Foo>::TestCopyConstructor(Foo(value1), Foo(value2), Foo(value3), Foo(value4));
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			std::uint32_t value4 = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestAssignmentOperator(value1, value2, value3, value4);
			VectorTestTemplate<std::uint32_t*>::TestAssignmentOperator(&value1, &value2, &value3, &value4);
			VectorTestTemplate<Foo>::TestAssignmentOperator(Foo(value1), Foo(value2), Foo(value3), Foo(value4));
		}

		TEST_METHOD(TestEmpty)
		{
			std::uint32_t value = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestEmpty(value);
			VectorTestTemplate<std::uint32_t*>::TestEmpty(&value);
			VectorTestTemplate<Foo>::TestEmpty(Foo(value));
		}

		TEST_METHOD(TestPushBack)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestPushBack(value1, value2);
			VectorTestTemplate<std::uint32_t*>::TestPushBack(&value1, &value2);
			VectorTestTemplate<Foo>::TestPushBack(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestPopBack)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestPopBack(value1, value2);
			VectorTestTemplate<std::uint32_t*>::TestPopBack(&value1, &value2);
			VectorTestTemplate<Foo>::TestPopBack(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestFront)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestFront(value1, value2);
			VectorTestTemplate<std::uint32_t*>::TestFront(&value1, &value2);
			VectorTestTemplate<Foo>::TestFront(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestBack)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestBack(value1, value2);
			VectorTestTemplate<std::uint32_t*>::TestBack(&value1, &value2);
			VectorTestTemplate<Foo>::TestBack(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestClear)
		{
			std::uint32_t value = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestClear(value);
			VectorTestTemplate<std::uint32_t*>::TestClear(&value);
			VectorTestTemplate<Foo>::TestClear(Foo(value));
		}

		TEST_METHOD(TestIndexOfOperator)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestIndexOfOperator(value1, value2);
			VectorTestTemplate<std::uint32_t*>::TestIndexOfOperator(&value1, &value2);
			VectorTestTemplate<Foo>::TestIndexOfOperator(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestFind)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestFind(value1, value2);
			VectorTestTemplate<std::uint32_t*>::TestFind(&value1, &value2);
			VectorTestTemplate<Foo>::TestFind(Foo(value1), Foo(value2));
		}

		TEST_METHOD(TestRemoveElement)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestRemoveElement(value1, value2, value3);
			VectorTestTemplate<std::uint32_t*>::TestRemoveElement(&value1, &value2, &value3);
			VectorTestTemplate<Foo>::TestRemoveElement(Foo(value1), Foo(value2), Foo(value3));
		}

		TEST_METHOD(TestRemoveElementRange)
		{
			std::uint32_t value1 = mHelper.GetRandomUInt32();
			std::uint32_t value2 = mHelper.GetRandomUInt32();
			std::uint32_t value3 = mHelper.GetRandomUInt32();
			std::uint32_t value4 = mHelper.GetRandomUInt32();
			VectorTestTemplate<std::uint32_t>::TestRemoveElementRange(value1, value2, value3, value4);
			VectorTestTemplate<std::uint32_t*>::TestRemoveElementRange(&value1, &value2, &value3, &value4);
			VectorTestTemplate<Foo>::TestRemoveElementRange(Foo(value1), Foo(value2), Foo(value3), Foo(value4));
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

	TestClassHelper VectorTest::mHelper;
}
