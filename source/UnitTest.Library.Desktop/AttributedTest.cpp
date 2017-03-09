#include "Pch.h"
#include "Attributed.h"
#include "AttributedFoo.h"
#include "AttributedBar.h"
#include "Datum.h"
#include "Vector.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	typedef AnonymousEngine::Attributed Attributed;
	typedef AnonymousEngine::Datum Datum;
	typedef Datum::DatumType DatumType;
	typedef AnonymousEngine::Vector<std::string> Vector;

	TEST_CLASS(AttributedTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			Attributed attributed;
			AttributedFoo foo;
			AttributedFoo bar;
		}

		TEST_METHOD(TestPrescribedAttributes)
		{
			Attributed attributed;
			AttributedFoo foo;
			AttributedBar bar;

			Assert::IsFalse(attributed.IsPrescribedAttribute(mHelper.GetRandomString()));
			Assert::IsFalse(foo.IsPrescribedAttribute(mHelper.GetRandomString()));
			Assert::IsFalse(bar.IsPrescribedAttribute(mHelper.GetRandomString()));

			for (auto& name : AttributedPrescribedAttributes)
			{
				Assert::IsTrue(attributed.IsPrescribedAttribute(name));
				Assert::IsTrue(foo.IsPrescribedAttribute(name));
				Assert::IsTrue(bar.IsPrescribedAttribute(name));
			}
			for (auto& name : AttributedFooPrescribedAttributes)
			{
				Assert::IsFalse(attributed.IsPrescribedAttribute(name));
				Assert::IsTrue(foo.IsPrescribedAttribute(name));
				Assert::IsTrue(bar.IsPrescribedAttribute(name));
			}
			for (auto& name : AttributedBarPrescribedAttributes)
			{
				Assert::IsFalse(attributed.IsPrescribedAttribute(name));
				Assert::IsFalse(foo.IsPrescribedAttribute(name));
				Assert::IsTrue(bar.IsPrescribedAttribute(name));
			}
			Assert::IsTrue(AttributedPrescribedAttributes == attributed.PrescribedAttributes());
			Assert::IsTrue(AttributedPrescribedAttributes == attributed.PrescribedAttributes());
			Assert::IsTrue(AttributedPrescribedAttributes == attributed.PrescribedAttributes());
		}

		TEST_METHOD(TestAttributes)
		{
			Attributed attributed;
			AttributedFoo foo;
			AttributedBar bar;

			std::uint32_t index = 0;
			for (auto& name : AuxiliaryAttributes)
			{
				initializers[index](attributed.AddAuxiliaryAttribute(name));
				initializers[index](foo.AddAuxiliaryAttribute(name + "Foo"));
				initializers[index](bar.AddAuxiliaryAttribute(name + "Bar"));
				++index;
			}

			Assert::IsFalse(attributed.IsAttribute(mHelper.GetRandomString()));
			Assert::IsFalse(foo.IsAttribute(mHelper.GetRandomString()));
			Assert::IsFalse(bar.IsAttribute(mHelper.GetRandomString()));

			for (auto& name : AttributedPrescribedAttributes)
			{
				Assert::IsTrue(attributed.IsAttribute(name));
				Assert::IsTrue(foo.IsAttribute(name));
				Assert::IsTrue(bar.IsAttribute(name));
			}
			for (auto& name : AttributedFooPrescribedAttributes)
			{
				Assert::IsFalse(attributed.IsAttribute(name));
				Assert::IsTrue(foo.IsAttribute(name));
				Assert::IsTrue(bar.IsAttribute(name));
			}
			for (auto& name : AttributedBarPrescribedAttributes)
			{
				Assert::IsFalse(attributed.IsAttribute(name));
				Assert::IsFalse(foo.IsAttribute(name));
				Assert::IsTrue(bar.IsAttribute(name));
			}

			for (auto& name : AuxiliaryAttributes)
			{
				Assert::IsTrue(attributed.IsAttribute(name));
				Assert::IsTrue(foo.IsAttribute(name + "Foo"));
				Assert::IsTrue(bar.IsAttribute(name + "Bar"));
			}

			Vector attributes = AttributedPrescribedAttributes;
			attributes.PushBack(AuxiliaryAttributes);
			
			Vector fooAttributes = AttributedPrescribedAttributes;
			fooAttributes.PushBack(AttributedFooPrescribedAttributes);
			Vector fooAuxAttributes = AuxiliaryAttributes;
			AddSuffixToStrings("Foo", fooAuxAttributes);
			
			Vector barAttributes = fooAttributes;
			fooAttributes.PushBack(fooAuxAttributes);

			barAttributes.PushBack(AttributedBarPrescribedAttributes);
			Vector barAuxAttributes = AuxiliaryAttributes;
			AddSuffixToStrings("Bar", barAuxAttributes);
			barAttributes.PushBack(barAuxAttributes);

			Vector temp;
			attributed.Attributes(temp);
			Assert::IsTrue(attributes == temp);
			foo.Attributes(temp);
			Assert::IsTrue(fooAttributes == temp);
			bar.Attributes(temp);
			Assert::IsTrue(barAttributes == temp);
		}

		TEST_METHOD(TestAuxiliaryAttributes)
		{
			Attributed attributed, attributed2;
			AttributedFoo foo, foo2;
			AttributedBar bar, bar2;

			std::uint32_t index = 0;
			for (auto& name : AuxiliaryAttributes)
			{
				initializers[index](attributed.AddAuxiliaryAttribute(name));
				initializers[index](foo.AddAuxiliaryAttribute(name + "Foo"));
				initializers[index](bar.AddAuxiliaryAttribute(name + "Bar"));
				++index;
			}

			Assert::IsFalse(attributed.IsAttribute(mHelper.GetRandomString()));
			Assert::IsFalse(foo.IsAttribute(mHelper.GetRandomString()));
			Assert::IsFalse(bar.IsAttribute(mHelper.GetRandomString()));

			for (auto& name : AttributedPrescribedAttributes)
			{
				Assert::IsFalse(attributed.IsAuxiliaryAttribute(name));
				Assert::IsFalse(foo.IsAuxiliaryAttribute(name));
				Assert::IsFalse(bar.IsAuxiliaryAttribute(name));
			}
			for (auto& name : AttributedFooPrescribedAttributes)
			{
				Assert::IsFalse(attributed.IsAuxiliaryAttribute(name));
				Assert::IsFalse(foo.IsAuxiliaryAttribute(name));
				Assert::IsFalse(bar.IsAuxiliaryAttribute(name));
			}
			for (auto& name : AttributedBarPrescribedAttributes)
			{
				Assert::IsFalse(attributed.IsAuxiliaryAttribute(name));
				Assert::IsFalse(foo.IsAuxiliaryAttribute(name));
				Assert::IsFalse(bar.IsAuxiliaryAttribute(name));
			}

			for (auto& name : AuxiliaryAttributes)
			{
				Assert::IsTrue(attributed.IsAuxiliaryAttribute(name));
				Assert::IsTrue(foo.IsAuxiliaryAttribute(name + "Foo"));
				Assert::IsTrue(bar.IsAuxiliaryAttribute(name + "Bar"));

				Assert::IsFalse(attributed2.IsAttribute(name));
				Assert::IsFalse(foo2.IsAttribute(name + "Foo"));
				Assert::IsFalse(bar2.IsAttribute(name + "Bar"));
				Assert::IsFalse(attributed2.IsAuxiliaryAttribute(name));
				Assert::IsFalse(foo2.IsAuxiliaryAttribute(name + "Foo"));
				Assert::IsFalse(bar2.IsAuxiliaryAttribute(name + "Bar"));
			}

			Vector fooAuxAttributes = AuxiliaryAttributes;
			AddSuffixToStrings("Foo", fooAuxAttributes);
			Vector barAuxAttributes = AuxiliaryAttributes;
			AddSuffixToStrings("Bar", barAuxAttributes);

			Vector temp;
			attributed.AuxiliaryAttributes(temp);
			Assert::IsTrue(AuxiliaryAttributes == temp);
			foo.AuxiliaryAttributes(temp);
			Assert::IsTrue(fooAuxAttributes == temp);
			bar.AuxiliaryAttributes(temp);
			Assert::IsTrue(barAuxAttributes == temp);
			
			attributed2.AuxiliaryAttributes(temp);
			Assert::IsTrue(temp.IsEmpty());
			foo2.AuxiliaryAttributes(temp);
			Assert::IsTrue(temp.IsEmpty());
			bar2.AuxiliaryAttributes(temp);
			Assert::IsTrue(temp.IsEmpty());
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
	private:

		static void AddSuffixToStrings(const std::string& suffix, Vector& vector);

		static const Vector AttributedPrescribedAttributes;
		static const Vector AttributedFooPrescribedAttributes;
		static const Vector AttributedBarPrescribedAttributes;
		static const Vector AuxiliaryAttributes;
		static const std::function<void(Datum&)> initializers[];
	};

	TestClassHelper AttributedTest::mHelper;

	const Vector AttributedTest::AttributedPrescribedAttributes = {
		"this"
	};
	const Vector AttributedTest::AttributedFooPrescribedAttributes = {
		"mInt",
		"mFloat",
		"mString",
		"mVec4",
		"mMat4",
		"mNestedScope",
		"mIntArray",
		"mFloatArray",
		"mStringArray",
		"mVec4Array",
		"mMat4Array",
		"mRTTIArray"
	};
	const Vector AttributedTest::AttributedBarPrescribedAttributes = {
		"mIntBar",
		"mFloatBar",
		"mStringBar",
		"mVec4Bar",
		"mMat4Bar",
		"mNestedScopeBar"
	};
	const Vector AttributedTest::AuxiliaryAttributes = {
		"testInt",
		"testFloat",
		"testString",
		"testVec4",
		"testMat4"
	};

	const std::function<void(Datum&)> AttributedTest::initializers[] = {
		[] (Datum& d) { d = mHelper.GetRandomInt32(); },
		[] (Datum& d) { d = mHelper.GetRandomFloat(); },
		[] (Datum& d) { d = mHelper.GetRandomString(); },
		[] (Datum& d) { d = mHelper.GetRandomVec4(); },
		[] (Datum& d) { d = mHelper.GetRandomMat4(); }
	};

	void AttributedTest::AddSuffixToStrings(const std::string& suffix, Vector& vector)
	{
		for (auto& data : vector)
		{
			data.append(suffix);
		}
	}
}
