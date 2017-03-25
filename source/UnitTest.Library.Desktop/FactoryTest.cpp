#include "Pch.h"
#include "Foo.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestLibraryDesktop
{
	using namespace AnonymousEngine;

	class InvalidFactory : public Factory<RTTI>
	{
	public:
		InvalidFactory()
		{
			Add(*this);
		}
		~InvalidFactory()
		{
			Remove(*this);
		}
		std::string ClassName() const override
		{
			return "Foo";
		}
		RTTI* Create() const override
		{
			return new Foo();
		}
	};

	TEST_CLASS(FactoryTest)
	{
	public:
		TEST_METHOD(TestAddAndRemove)
		{
			InvalidFactory invalid;
			Factory<RTTI>::Remove(invalid);
			FooFactory f;
			Assert::ExpectException<std::runtime_error>([] { InvalidFactory invalid; });
			Assert::IsTrue(Factory<RTTI>::Remove(f));
			Assert::IsFalse(Factory<RTTI>::Remove(f));
		}

		TEST_METHOD(TestCreate)
		{
			FooFactory fooFactory;
			Assert::ExpectException<std::runtime_error>([] { Factory<RTTI>::Create(mHelper.GetRandomString()); });

			Foo* foo = fooFactory.Create()->As<Foo>();
			Assert::IsNotNull(foo);
			delete foo;

			foo = Factory<RTTI>::Create("Foo")->As<Foo>();
			Assert::IsNotNull(foo);
			delete foo;

			Factory<RTTI>::Remove(fooFactory);
		}

		TEST_METHOD(TestFind)
		{
			FooFactory fooFactory;
			Assert::IsTrue(&fooFactory == Factory<RTTI>::Find("Foo"));
			Assert::IsNull(Factory<RTTI>::Find(mHelper.GetRandomString()));
			Factory<RTTI>::Remove(fooFactory);
		}

		TEST_METHOD(TestBeginAndEnd)
		{
			FooFactory fooFactory;
			Assert::IsFalse(Factory<RTTI>::begin() == Factory<RTTI>::end());
			std::uint32_t size = 0;
			for(auto it = Factory<RTTI>::begin(); it != Factory<RTTI>::end(); ++it)
			{
				++size;
			}
			Assert::AreEqual(1U, size);
			Assert::IsTrue(&fooFactory == (Factory<RTTI>::begin())->second);
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

		static TestClassHelper mHelper;
	};

	TestClassHelper FactoryTest::mHelper;
}
