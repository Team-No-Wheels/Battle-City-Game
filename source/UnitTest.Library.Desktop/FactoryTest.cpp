#include "Pch.h"
#include "Foo.h"
#include "TestClassHelper.h"
#include "Bar.h"
#include "DerivedBar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestLibraryDesktop
{
	using namespace AnonymousEngine;

	class InvalidRTTIFactory : public Factory<RTTI>
	{
	public:
		InvalidRTTIFactory()
		{
			Add(*this);
		}
		~InvalidRTTIFactory()
		{
			Remove(ClassName());
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

	class InvalidBarFactory : public Factory<Bar>
	{
	public:
		InvalidBarFactory()
		{
			Add(*this);
		}
		~InvalidBarFactory()
		{
			Remove(ClassName());
		}
		std::string ClassName() const override
		{
			return "DerivedBar";
		}
		Bar* Create() const override
		{
			return new Bar();
		}
	};

	TEST_CLASS(FactoryTest)
	{
	public:
		TEST_METHOD(TestAddAndRemove)
		{
			InvalidRTTIFactory invalid;
			Assert::IsTrue(Factory<RTTI>::Remove(invalid.ClassName()));
			FooFactory f;
			Assert::ExpectException<std::runtime_error>([] { InvalidRTTIFactory invalid; });
			Assert::IsTrue(Factory<RTTI>::Remove(f.ClassName()));
			Assert::IsFalse(Factory<RTTI>::Remove(f.ClassName()));

			InvalidBarFactory invalidBar;
			Assert::IsTrue(Factory<Bar>::Remove(invalidBar.ClassName()));
			DerivedBarFactory b;
			Assert::ExpectException<std::runtime_error>([] { InvalidBarFactory invalid; });
			Assert::IsTrue(Factory<Bar>::Remove(b.ClassName()));
			Assert::IsFalse(Factory<Bar>::Remove(b.ClassName()));
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
			Factory<RTTI>::Remove(fooFactory.ClassName());

			DerivedBarFactory barFactory;
			Assert::ExpectException<std::runtime_error>([] { Factory<Bar>::Create(mHelper.GetRandomString()); });
			DerivedBar* bar = static_cast<DerivedBar*>(barFactory.Create());
			Assert::IsNotNull(bar);
			delete bar;
			bar = static_cast<DerivedBar*>(Factory<Bar>::Create("DerivedBar"));
			Assert::IsNotNull(foo);
			delete bar;
			Factory<Bar>::Remove(barFactory.ClassName());
		}

		TEST_METHOD(TestFind)
		{
			FooFactory fooFactory;
			DerivedBarFactory barFactory;

			Assert::IsTrue(&fooFactory == Factory<RTTI>::Find(fooFactory.ClassName()));
			Assert::IsNull(Factory<RTTI>::Find(mHelper.GetRandomString()));
			Assert::IsNull(Factory<RTTI>::Find(barFactory.ClassName()));

			Assert::IsTrue(&barFactory == Factory<Bar>::Find(barFactory.ClassName()));
			Assert::IsNull(Factory<Bar>::Find(mHelper.GetRandomString()));
			Assert::IsNull(Factory<Bar>::Find(fooFactory.ClassName()));

			Factory<RTTI>::Remove(fooFactory.ClassName());
			Factory<Bar>::Remove(fooFactory.ClassName());
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

			DerivedBarFactory barFactory;
			Assert::IsFalse(Factory<Bar>::begin() == Factory<Bar>::end());
			std::uint32_t barSize = 0;
			for (auto it = Factory<Bar>::begin(); it != Factory<Bar>::end(); ++it)
			{
				++barSize;
			}
			Assert::AreEqual(1U, barSize);
			Assert::IsTrue(&barFactory == (Factory<Bar>::begin())->second);
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
