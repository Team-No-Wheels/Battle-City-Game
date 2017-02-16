#include "Pch.h"
#include "Foo.h"
#include "DatumTestTemplate.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			inline std::wstring ToString<AnonymousEngine::Datum::DatumType>(const AnonymousEngine::Datum::DatumType& type)
			{
				return std::to_wstring(static_cast<std::uint32_t>(type));
			}
		}
	}
}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(DatumTest)
	{
	public:
		typedef std::function<void(DatumType type)> TestMethodNoParam;

		TEST_METHOD(TestDefaultConstructor)
		{
			TestDatumForAllTypes(&DatumTest::DefaultConstructorTest, true);
		}

		TEST_METHOD(TestSetType)
		{
			TestDatumForAllTypes(&DatumTest::SetTypeTest);
		}

		TEST_METHOD(TestCopyConstructor)
		{
			DatumTestTemplate<std::int32_t>::TestCopyConstructor(mHelper.GetRandomInt32(), mHelper.GetRandomInt32());
			DatumTestTemplate<float>::TestCopyConstructor(mHelper.GetRandomFloat(), mHelper.GetRandomFloat());
			DatumTestTemplate<std::string>::TestCopyConstructor(mHelper.GetRandomString(), mHelper.GetRandomString());
			DatumTestTemplate<glm::vec4>::TestCopyConstructor(mHelper.GetRandomVec4(), mHelper.GetRandomVec4());
			DatumTestTemplate<glm::mat4>::TestCopyConstructor(mHelper.GetRandomMat4(), mHelper.GetRandomMat4());
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestCopyConstructor(&f1, &f2);
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			DatumTestTemplate<std::int32_t>::TestAssignmentOperator(mHelper.GetRandomInt32(), mHelper.GetRandomInt32());
			DatumTestTemplate<float>::TestAssignmentOperator(mHelper.GetRandomFloat(), mHelper.GetRandomFloat());
			DatumTestTemplate<std::string>::TestAssignmentOperator(mHelper.GetRandomString(), mHelper.GetRandomString());
			DatumTestTemplate<glm::vec4>::TestAssignmentOperator(mHelper.GetRandomVec4(), mHelper.GetRandomVec4());
			DatumTestTemplate<glm::mat4>::TestAssignmentOperator(mHelper.GetRandomMat4(), mHelper.GetRandomMat4());
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestAssignmentOperator(&f1, &f2);
		}

		TEST_METHOD(TestAssignmentScalar)
		{
			DatumTestTemplate<std::int32_t>::TestAssignmentScalar(DatumType::Integer, mHelper.GetRandomInt32(), mHelper.GetRandomInt32(), DatumType::Float);
			DatumTestTemplate<float>::TestAssignmentScalar(DatumType::Float, mHelper.GetRandomFloat(), mHelper.GetRandomFloat(), DatumType::Integer);
			DatumTestTemplate<std::string>::TestAssignmentScalar(DatumType::String, mHelper.GetRandomString(), mHelper.GetRandomString(), DatumType::Vector);
			DatumTestTemplate<glm::vec4>::TestAssignmentScalar(DatumType::Vector, mHelper.GetRandomVec4(), mHelper.GetRandomVec4(), DatumType::Matrix);
			DatumTestTemplate<glm::mat4>::TestAssignmentScalar(DatumType::Matrix, mHelper.GetRandomMat4(), mHelper.GetRandomMat4(), DatumType::Integer);
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestAssignmentScalar(DatumType::RTTI, &f1, &f2, DatumType::Float);
		}

		TEST_METHOD(TestGet)
		{
			DatumTestTemplate<std::int32_t>::TestGet(mHelper.GetRandomInt32(), mHelper.GetRandomInt32());
			DatumTestTemplate<float>::TestGet(mHelper.GetRandomFloat(), mHelper.GetRandomFloat());
			DatumTestTemplate<std::string>::TestGet(mHelper.GetRandomString(), mHelper.GetRandomString());
			DatumTestTemplate<glm::vec4>::TestGet(mHelper.GetRandomVec4(), mHelper.GetRandomVec4());
			DatumTestTemplate<glm::mat4>::TestGet(mHelper.GetRandomMat4(), mHelper.GetRandomMat4());
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestGet(&f1, &f2);

			/*DatumTestTemplate<std::int32_t>::TestConstantGet(mHelper.GetRandomInt32());
			DatumTestTemplate<float>::TestConstantGet(mHelper.GetRandomFloat());
			DatumTestTemplate<std::string>::TestConstantGet(mHelper.GetRandomString());
			DatumTestTemplate<glm::vec4>::TestConstantGet(mHelper.GetRandomVec4());
			DatumTestTemplate<glm::mat4>::TestConstantGet(mHelper.GetRandomMat4());
			DatumTestTemplate<RTTI*>::TestConstantGet(&f1);*/
		}

		TEST_METHOD(TestSet)
		{
			DatumTestTemplate<std::int32_t>::TestSet(DatumType::Integer, mHelper.GetRandomInt32(), mHelper.GetRandomInt32(), DatumType::Float);
			DatumTestTemplate<float>::TestSet(DatumType::Float, mHelper.GetRandomFloat(), mHelper.GetRandomFloat(), DatumType::Integer);
			DatumTestTemplate<std::string>::TestSet(DatumType::String, mHelper.GetRandomString(), mHelper.GetRandomString(), DatumType::Vector);
			DatumTestTemplate<glm::vec4>::TestSet(DatumType::Vector, mHelper.GetRandomVec4(), mHelper.GetRandomVec4(), DatumType::Matrix);
			DatumTestTemplate<glm::mat4>::TestSet(DatumType::Matrix, mHelper.GetRandomMat4(), mHelper.GetRandomMat4(), DatumType::Integer);
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestSet(DatumType::RTTI, &f1, &f2, DatumType::Float);
		}

		TEST_METHOD(TestPushBack)
		{
			DatumTestTemplate<std::int32_t>::TestPushBack(DatumType::Integer, mHelper.GetRandomInt32(), mHelper.GetRandomInt32());
			DatumTestTemplate<float>::TestPushBack(DatumType::Float, mHelper.GetRandomFloat(), mHelper.GetRandomFloat());
			DatumTestTemplate<std::string>::TestPushBack(DatumType::String, mHelper.GetRandomString(), mHelper.GetRandomString());
			DatumTestTemplate<glm::vec4>::TestPushBack(DatumType::Vector, mHelper.GetRandomVec4(), mHelper.GetRandomVec4());
			DatumTestTemplate<glm::mat4>::TestPushBack(DatumType::Matrix, mHelper.GetRandomMat4(), mHelper.GetRandomMat4());
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestPushBack(DatumType::RTTI, &f1, &f2);
		}

		TEST_METHOD(TestResize)
		{
			DatumTestTemplate<std::int32_t>::TestResize(DatumType::Integer, mHelper.GetRandomInt32(), mHelper.GetRandomInt32());
			DatumTestTemplate<float>::TestResize(DatumType::Float, mHelper.GetRandomFloat(), mHelper.GetRandomFloat());
			DatumTestTemplate<std::string>::TestResize(DatumType::String, mHelper.GetRandomString(), mHelper.GetRandomString());
			DatumTestTemplate<glm::vec4>::TestResize(DatumType::Vector, mHelper.GetRandomVec4(), mHelper.GetRandomVec4());
			DatumTestTemplate<glm::mat4>::TestResize(DatumType::Matrix, mHelper.GetRandomMat4(), mHelper.GetRandomMat4());
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestResize(DatumType::RTTI, &f1, &f2);
		}

		TEST_METHOD(TestPopBack)
		{
			DatumTestTemplate<std::int32_t>::TestPopBack(DatumType::Integer, mHelper.GetRandomInt32(), mHelper.GetRandomInt32());
			DatumTestTemplate<float>::TestPopBack(DatumType::Float, mHelper.GetRandomFloat(), mHelper.GetRandomFloat());
			DatumTestTemplate<std::string>::TestPopBack(DatumType::String, mHelper.GetRandomString(), mHelper.GetRandomString());
			DatumTestTemplate<glm::vec4>::TestPopBack(DatumType::Vector, mHelper.GetRandomVec4(), mHelper.GetRandomVec4());
			DatumTestTemplate<glm::mat4>::TestPopBack(DatumType::Matrix, mHelper.GetRandomMat4(), mHelper.GetRandomMat4());
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestPopBack(DatumType::RTTI, &f1, &f2);
		}

		TEST_METHOD(TestEqualsOperator)
		{
			DatumTestTemplate<std::int32_t>::TestEqualsOperator(mHelper.GetRandomInt32(), mHelper.GetRandomInt32());
			float float1 = mHelper.GetRandomFloat();
			float float2 = float1 + 100;
			DatumTestTemplate<float>::TestEqualsOperator(float1, float2);
			DatumTestTemplate<std::string>::TestEqualsOperator(mHelper.GetRandomString(), mHelper.GetRandomString());
			DatumTestTemplate<glm::vec4>::TestEqualsOperator(mHelper.GetRandomVec4(), mHelper.GetRandomVec4());
			DatumTestTemplate<glm::mat4>::TestEqualsOperator(mHelper.GetRandomMat4(), mHelper.GetRandomMat4());
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestEqualsOperator(&f1, &f2);
		}

		TEST_METHOD(TestNotEqualsOperator)
		{
			DatumTestTemplate<std::int32_t>::TestNotEqualsOperator(mHelper.GetRandomInt32(), mHelper.GetRandomInt32());
			float float1 = mHelper.GetRandomFloat();
			float float2 = float1 + 100;
			DatumTestTemplate<float>::TestNotEqualsOperator(float1, float2);
			DatumTestTemplate<std::string>::TestNotEqualsOperator(mHelper.GetRandomString(), mHelper.GetRandomString());
			DatumTestTemplate<glm::vec4>::TestNotEqualsOperator(mHelper.GetRandomVec4(), mHelper.GetRandomVec4());
			DatumTestTemplate<glm::mat4>::TestNotEqualsOperator(mHelper.GetRandomMat4(), mHelper.GetRandomMat4());
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestNotEqualsOperator(&f1, &f2);
		}

		TEST_METHOD(TestSetStorage)
		{
			DatumTestTemplate<std::int32_t>::TestSetStorage(DatumType::Integer, mHelper.GetRandomInt32(), mHelper.GetRandomInt32(), DatumType::Float);
			DatumTestTemplate<float>::TestSetStorage(DatumType::Float, mHelper.GetRandomFloat(), mHelper.GetRandomFloat(), DatumType::Integer);
			DatumTestTemplate<std::string>::TestSetStorage(DatumType::String, mHelper.GetRandomString(), mHelper.GetRandomString(), DatumType::Vector);
			DatumTestTemplate<glm::vec4>::TestSetStorage(DatumType::Vector, mHelper.GetRandomVec4(), mHelper.GetRandomVec4(), DatumType::Matrix);
			DatumTestTemplate<glm::mat4>::TestSetStorage(DatumType::Matrix, mHelper.GetRandomMat4(), mHelper.GetRandomMat4(), DatumType::Integer);
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestSetStorage(DatumType::RTTI, &f1, &f2, DatumType::Float);
		}

		TEST_METHOD(TestToAndFromString)
		{
			DatumTestTemplate<std::int32_t>::TestToAndFromString(mHelper.GetRandomInt32(), mHelper.GetRandomInt32(), mHelper.GetRandomInt32(),
				mHelper.GetRandomInt32(), &DatumTest::Compare<std::int32_t>);
			float float1 = mHelper.GetRandomFloat();
			float float2 = float1 + 100;
			float float3 = 200;
			float float4 = 400;
			DatumTestTemplate<float>::TestToAndFromString(float1, float2, float3, float4, &DatumTest::Compare<float>);
			DatumTestTemplate<std::string>::TestToAndFromString(mHelper.GetRandomString(), mHelper.GetRandomString(), mHelper.GetRandomString(),
				mHelper.GetRandomString(), &DatumTest::Compare<std::string>);
			DatumTestTemplate<glm::vec4>::TestToAndFromString(mHelper.GetRandomVec4(), mHelper.GetRandomVec4(), mHelper.GetRandomVec4(),
				mHelper.GetRandomVec4(), &DatumTest::Compare<glm::vec4>);
			DatumTestTemplate<glm::mat4>::TestToAndFromString(mHelper.GetRandomMat4(), mHelper.GetRandomMat4(), mHelper.GetRandomMat4(),
				mHelper.GetRandomMat4(), &DatumTest::Compare<glm::mat4>);
			Foo f1 = mHelper.GetRandomFoo();
			Foo f2 = mHelper.GetRandomFoo();
			Foo f3 = mHelper.GetRandomFoo();
			Foo f4 = mHelper.GetRandomFoo();
			DatumTestTemplate<RTTI*>::TestToAndFromString(&f1, &f2, &f3, &f4, &DatumTest::Compare<RTTI*>);
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

		static void SetTypeTest(DatumType type)
		{
			Datum d;
			Assert::AreEqual(DatumType::Unknown, d.Type());
			d.SetType(type);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(0U, d.Size());
		}

		static void DefaultConstructorTest(DatumType type)
		{
			Datum d(type);
			Assert::AreEqual(type, d.Type());
			Assert::AreEqual(0U, d.Size());
		}

		// repeats test for all the enum values (optional argument to start from Unknown type instead of Integer type
		static void TestDatumForAllTypes(TestMethodNoParam method, bool testUnknown = false)
		{
			std::uint32_t index;
			if (testUnknown)
			{
				index = static_cast<std::uint32_t>(DatumType::Unknown);
			}
			else
			{
				index = static_cast<std::uint32_t>(DatumType::Integer);
			}

			for (; index < static_cast<std::uint32_t>(DatumType::MaxTypes); ++index)
			{
				method(static_cast<DatumType>(index));
			}
		}

		template<typename T>
		static bool Compare(const T& a, const T& b)
		{
			return (a == b);
		}

		template<>
		static bool Compare<float>(const float& a, const float& b)
		{
			return (std::fabs(a - b) < 0.00001);
		}

		template<>
		static bool Compare<glm::vec4>(const glm::vec4& a, const glm::vec4& b)
		{
			return (Compare<float>(a.x, b.x) && Compare(a.y, b.y) && Compare(a.z, b.z) && Compare(a.w, b.w));
		}

		template<>
		static bool Compare<glm::mat4>(const glm::mat4& a, const glm::mat4& b)
		{
			return (Compare<glm::vec4>(a[0], b[0]) && Compare(a[1], b[1]) && Compare(a[2], b[2]) && Compare(a[3], b[3]));
		}

		template<>
		static bool Compare<RTTI*>(RTTI* const& a, RTTI* const& b)
		{
			return dynamic_cast<Foo*>(a)->Data() == dynamic_cast<Foo*>(b)->Data();
		}

		static TestClassHelper mHelper;
	};

	TestClassHelper DatumTest::mHelper;
}
