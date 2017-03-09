#include "Pch.h"
#include "Foo.h"
#include "Scope.h"
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
	TEST_CLASS(ScopeTest)
	{
	public:
		typedef AnonymousEngine::Datum Datum;
		typedef Datum::DatumType DatumType;
		typedef AnonymousEngine::Scope Scope;
		typedef AnonymousEngine::RTTI RTTI;

		TEST_METHOD(TestDefaultConstructor)
		{
			Scope s;
			Assert::IsTrue(nullptr == s.GetParent());
		}

		TEST_METHOD(TestAppend)
		{
			Scope s;
			Datum& d1 = s.Append("test");
			Assert::AreEqual(DatumType::Unknown, d1.Type());
			
			std::int32_t value = mHelper.GetRandomInt32();
			Datum d2;
			d1 = value;
			d2 = value;
			Assert::IsTrue(d1 == d2);
			Assert::IsTrue(d1 == s.Append("test"));
			Assert::IsTrue(&d1 == &s.Append("test"));
			Assert::IsTrue(&d1 == &s["test"]);
			Assert::IsTrue(&d1 == &const_cast<const Scope&>(s)["test"]);
			
			Datum& d3 = s.Append("foo");
			Foo* foo = new Foo();
			d3 = foo;
			Assert::IsTrue(d3 == foo);

			Datum& d4 = s["newInt"];
			d4 = mHelper.GetRandomInt32();
			Assert::IsTrue(s["newInt"] == d4);
			Assert::ExpectException<std::invalid_argument>([&s] { const_cast<const Scope&>(s)["newIntNotFound"]; });

			Assert::IsTrue(s[0U] == d1);
			Assert::IsTrue(s[1U] == d3);
			Assert::IsTrue(s[2U] == d4);
			Assert::IsTrue(const_cast<const Scope&>(s)[2U] == d4);
			delete foo;
		}

		TEST_METHOD(TestAppendScope)
		{
			std::int32_t value1 = mHelper.GetRandomInt32();
			Scope scope;
			Datum& d1 = scope.Append("test");
			d1 = value1;
			Assert::AreEqual(DatumType::Integer, d1.Type());
			
			std::int32_t value2 = mHelper.GetRandomInt32();
			Scope& childScope = scope.AppendScope("child");
			Datum &d2 = childScope.Append("childTest");
			d2 = value2;
			Datum& d = scope.Append("child");
			
			Assert::AreEqual(DatumType::Integer, d2.Type());
			Assert::IsTrue(d2 == value2);
			Assert::IsTrue(childScope.GetParent() == const_cast<const Scope*>(&scope));
			Assert::AreEqual(1U, d.Size());

			Scope& childScope2 = scope.AppendScope("child");
			Assert::IsTrue(childScope != childScope2);
			Assert::IsTrue(childScope2.GetParent() == const_cast<const Scope*>(&scope));

			Assert::AreEqual(2U, d.Size());
			scope.AppendScope("child");
			Assert::AreEqual(3U, d.Size());
		}

		TEST_METHOD(TestCopySemantics)
		{
			std::int32_t int1 = mHelper.GetRandomInt32();
			std::string str1 = mHelper.GetRandomString();
			Scope scope;
			Datum& dInt1 = scope.Append("int");
			dInt1 = int1;
			Datum& dStr1 = scope.Append("string");
			dStr1 = str1;

			std::int32_t int2 = mHelper.GetRandomInt32();
			Scope& childScope = scope.AppendScope("child");
			Datum &dInt2 = childScope.Append("childInt");
			dInt2 = int2;

			std::int32_t int3 = mHelper.GetRandomInt32();
			Scope& childScope2 = scope.AppendScope("child");
			Datum& dInt3 = childScope2.Append("child2Int");
			dInt3 = int3;

			std::int32_t int4 = mHelper.GetRandomInt32();
			Scope& grandChildScope = childScope.AppendScope("grandChild");
			Datum &dInt4 = grandChildScope.Append("grandChildInt");
			dInt4 = int4;

			Scope newScope(scope);
			Assert::IsTrue(newScope.Append("int") == dInt1);
			Assert::IsTrue(newScope.Append("string") == dStr1);
			Scope& newChildScope = newScope.Append("child").Get<Scope>();
			Scope& newChildScope2 = newScope.Append("child").Get<Scope>(1U);
			Assert::IsTrue(newChildScope.Append("childInt") == dInt2);
			Assert::IsTrue(newChildScope2.Append("child2Int") == dInt3);
			Scope& newGrandChildScope = newChildScope.Append("grandChild").Get<Scope>();
			Assert::IsTrue(newGrandChildScope.Append("grandChildInt") == dInt4);

			Scope copyScope;
			copyScope = scope;
			Assert::IsTrue(copyScope.Append("int") == dInt1);
			Assert::IsTrue(copyScope.Append("string") == dStr1);
			Scope& copyChildScope = copyScope.Append("child").Get<Scope>();
			Scope& copyChildScope2 = copyScope.Append("child").Get<Scope>(1U);
			Assert::IsTrue(copyChildScope.Append("childInt") == dInt2);
			Assert::IsTrue(copyChildScope2.Append("child2Int") == dInt3);
			Scope& copyGrandChildScope = copyChildScope.Append("grandChild").Get<Scope>();
			Assert::IsTrue(copyGrandChildScope.Append("grandChildInt") == dInt4);
		}

		TEST_METHOD(TestMoveSemantics)
		{
			std::int32_t int1 = mHelper.GetRandomInt32();
			std::string str1 = mHelper.GetRandomString();
			Scope* scope = new Scope();
			Datum& dInt1 = scope->Append("int");
			dInt1 = int1;
			Datum& dStr1 = scope->Append("string");
			dStr1 = str1;

			std::int32_t int2 = mHelper.GetRandomInt32();
			Scope& childScope = scope->AppendScope("child");
			Datum &dInt2 = childScope.Append("childInt");
			dInt2 = int2;

			std::int32_t int3 = mHelper.GetRandomInt32();
			Scope& childScope2 = scope->AppendScope("child");
			Datum& dInt3 = childScope2.Append("child2Int");
			dInt3 = int3;

			std::int32_t int4 = mHelper.GetRandomInt32();
			Scope& grandChildScope = childScope.AppendScope("grandChild");
			Datum &dInt4 = grandChildScope.Append("grandChildInt");
			dInt4 = int4;

			Scope* scope2 = new Scope(*scope);
			Scope newScope(std::move(*scope));
			delete scope;

			Assert::IsTrue(newScope.Append("int") == dInt1);
			Assert::IsTrue(newScope.Append("string") == dStr1);
			Scope& newChildScope = newScope.Append("child").Get<Scope>();
			Scope& newChildScope2 = newScope.Append("child").Get<Scope>(1U);
			Assert::IsTrue(newChildScope.Append("childInt") == dInt2);
			Assert::IsTrue(newChildScope2.Append("child2Int") == dInt3);
			Scope& newGrandChildScope = newChildScope.Append("grandChild").Get<Scope>();
			Assert::IsTrue(newGrandChildScope.Append("grandChildInt") == dInt4);
			
			Scope& copyScope = *(new Scope());
			copyScope.Append("int") = dInt1;
			copyScope.Append("string") = dStr1;
			copyScope = std::move(*scope2);
			delete scope2;
			
			Assert::IsTrue(copyScope.Append("int") == dInt1);
			Assert::IsTrue(copyScope.Append("string") == dStr1);
			Scope& copyChildScope = copyScope.Append("child").Get<Scope>();
			Scope& copyChildScope2 = copyScope.Append("child").Get<Scope>(1U);
			Assert::IsTrue(copyChildScope.Append("childInt") == dInt2);
			Assert::IsTrue(copyChildScope2.Append("child2Int") == dInt3);
			Scope& copyGrandChildScope = copyChildScope.Append("grandChild").Get<Scope>();
			Assert::IsTrue(copyGrandChildScope.Append("grandChildInt") == dInt4);

			Scope s;
			s.Adopt(copyScope, "test");
			//Scope t = std::move(copyScope);
		}

		TEST_METHOD(TestFind)
		{
			std::int32_t int1 = mHelper.GetRandomInt32();
			std::string str1 = mHelper.GetRandomString();
			Scope scope;
			Datum& dInt1 = scope.Append("int");
			dInt1 = int1;
			Datum& dStr1 = scope.Append("string");
			dStr1 = str1;

			std::int32_t int2 = mHelper.GetRandomInt32();
			Scope& childScope = scope.AppendScope("child");
			Datum &dInt2 = childScope.Append("int");
			dInt2 = int2;

			Assert::IsTrue(dInt1 == *scope.Find("int"));
			Assert::IsTrue(nullptr == scope.Find("int2"));
			Assert::IsTrue(dInt2 == *childScope.Find("int"));
			Assert::IsTrue(nullptr == childScope.Find("string"));
			Assert::IsTrue(dStr1 == *scope.Find("string"));
			Assert::IsTrue(dInt1 == *const_cast<const Scope&>(scope).Find("int"));
		}

		TEST_METHOD(TestSearch)
		{
			std::int32_t int1 = mHelper.GetRandomInt32();
			std::string str1 = mHelper.GetRandomString();
			Scope scope;
			Datum& dInt1 = scope.Append("int");
			dInt1 = int1;
			Datum& dStr1 = scope.Append("string");
			dStr1 = str1;

			std::int32_t int2 = mHelper.GetRandomInt32();
			Scope& childScope = scope.AppendScope("child");
			Datum &dInt2 = childScope.Append("int");
			dInt2 = int2;

			Assert::IsTrue(dInt1 == *scope.Search("int"));
			Assert::IsTrue(nullptr == scope.Search("int2"));
			Assert::IsTrue(dInt2 == *childScope.Search("int"));
			Assert::IsTrue(dStr1 == *childScope.Search("string"));
			Scope* foundScope;
			Assert::IsTrue(dStr1 == *childScope.Search("string", &foundScope));
			Assert::IsTrue(foundScope == &scope);
			Assert::IsTrue(dStr1 == *scope.Search("string"));
			Assert::IsTrue(dStr1 == *const_cast<const Scope&>(scope).Search("string"));
		}

		TEST_METHOD(TestAdopt)
		{
			std::int32_t int1 = mHelper.GetRandomInt32();
			std::string str1 = mHelper.GetRandomString();
			Scope scope;
			Datum& dInt1 = scope.Append("int");
			dInt1 = int1;
			Datum& dStr1 = scope.Append("string");
			dStr1 = str1;
			std::int32_t int2 = mHelper.GetRandomInt32();
			Scope& childScope = scope.AppendScope("child");
			Datum &dInt2 = childScope.Append("int");
			dInt2 = int2;

			Assert::IsTrue(scope["child"].Get<Scope>() == childScope);
			Assert::IsNotNull(scope.Find("child"));
			Assert::IsTrue(childScope.GetParent() == &scope);
			Scope scope2;
			scope2.Adopt(childScope, "newChild");
			Assert::IsTrue(scope["child"].Size() == 0U);
			Assert::IsNull(scope2.Find("child"));
			Assert::IsTrue(scope2["newChild"].Get<Scope>() == childScope);
			Assert::IsTrue(childScope.GetParent() == &scope2);
			Assert::IsFalse(childScope.Equals(nullptr));
			Foo f;
			Assert::IsFalse(childScope.Equals(&f));
			Datum d;
			d = &scope;

			Assert::ExpectException<std::invalid_argument>([&scope] { scope.Adopt(scope, "test"); });
		}

		TEST_METHOD(TestRTTI)
		{
			Scope scope;
			Scope* s = &scope;
			RTTI* t = s;
			Assert::IsTrue(s->Is(Scope::TypeIdClass()));
			Assert::IsTrue(s->Is(s->TypeIdInstance()));
			Assert::IsTrue(s->Is("Scope"));
			Assert::IsFalse(s->Is(Foo::TypeIdClass()));
			Assert::IsFalse(s->Is("Foo"));
			Assert::IsNotNull(s->As<Scope>());
			Assert::IsNull(t->As<Foo>());
			Assert::IsNotNull(t->As<Scope>());
			Assert::IsNotNull(t->QueryInterface(Scope::TypeIdClass()));
			Assert::IsNull(t->QueryInterface(Foo::TypeIdClass()));
		}

		TEST_METHOD(TestToStringAndSetFromString)
		{
			Scope s;
			Assert::ExpectException<std::runtime_error>([&s] { s.FromString(s.ToString()); });
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

	TestClassHelper ScopeTest::mHelper;
}
