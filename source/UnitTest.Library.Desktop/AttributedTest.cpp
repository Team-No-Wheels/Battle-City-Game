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
	typedef AnonymousEngine::Scope Scope;
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

			Assert::ExpectException<std::invalid_argument>([]()
			{
				AttributedBar barValidateAttributeFail(AttributedBar::TestScenario::ValidateAttributeFail);
			});

			Assert::ExpectException<std::runtime_error>([]()
			{
				AttributedBar barValidateAllAttributesFail(AttributedBar::TestScenario::ValidateAllAttributesFail);
			});
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

			Assert::IsTrue(attributes == attributed.Attributes());
			Assert::IsTrue(fooAttributes == foo.Attributes());
			Assert::IsTrue(barAttributes == bar.Attributes());
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

			Assert::IsTrue(AuxiliaryAttributes == attributed.AuxiliaryAttributes());
			Assert::IsTrue(fooAuxAttributes == foo.AuxiliaryAttributes());
			Assert::IsTrue(barAuxAttributes == bar.AuxiliaryAttributes());
			
			Assert::IsTrue(attributed2.AuxiliaryAttributes().IsEmpty());
			Assert::IsTrue(foo2.AuxiliaryAttributes().IsEmpty());
			Assert::IsTrue(bar2.AuxiliaryAttributes().IsEmpty());
		}

		TEST_METHOD(TestCopySemantics)
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

			Attributed attributed2 (attributed);
			AttributedFoo foo2 (foo);
			AttributedBar bar2 (bar);

			Assert::IsTrue(attributed.Attributes() == attributed2.Attributes());
			Assert::IsTrue(foo.Attributes() == foo2.Attributes());
			Assert::IsTrue(bar.Attributes() == bar2.Attributes());

			Attributed attributed3;
			attributed3 = attributed;
			AttributedFoo foo3;
			foo3 = foo;
			AttributedBar bar3;
			bar3 = bar;

			Assert::IsTrue(attributed.Attributes() == attributed3.Attributes());
			Assert::IsTrue(foo.Attributes() == foo3.Attributes());
			Assert::IsTrue(bar.Attributes() == bar3.Attributes());
		}

		TEST_METHOD(TestMoveSemantics)
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

			Attributed attributedBackup = attributed;
			AttributedFoo fooBackup = foo;
			AttributedBar barBackup = bar;
			Attributed attributedBackup2 = attributed;
			AttributedFoo fooBackup2 = foo;
			AttributedBar barBackup2 = bar;

			Attributed attributed2(std::move(attributed));
			AttributedFoo foo2(std::move(foo));
			AttributedBar bar2 (std::move(bar));

			Assert::IsTrue(attributedBackup.Attributes() == attributed2.Attributes());
			Assert::IsTrue(fooBackup.Attributes() == foo2.Attributes());
			Assert::IsTrue(barBackup.Attributes() == bar2.Attributes());

			Attributed attributed3;
			attributed3 = std::move(attributedBackup);
			AttributedFoo foo3;
			foo3 = std::move(fooBackup);
			AttributedBar bar3;
			bar3 = std::move(barBackup);

			Assert::IsTrue(attributedBackup2.Attributes() == attributed3.Attributes());
			Assert::IsTrue(fooBackup2.Attributes() == foo3.Attributes());
			Assert::IsTrue(barBackup2.Attributes() == bar3.Attributes());
		}

		TEST_METHOD(TestTwoWaySet)
		{
			AttributedFoo foo;
			AttributedBar bar;

			foo.mInt = mHelper.GetRandomInt32();
			foo.mFloat = mHelper.GetRandomFloat();
			foo.mString = mHelper.GetRandomString();
			foo.mVec4 = mHelper.GetRandomVec4();
			foo.mMat4 = mHelper.GetRandomMat4();

			Assert::AreEqual(foo["mInt"].Get<std::int32_t>(), foo.mInt);
			Assert::AreEqual(foo["mFloat"].Get<float>(), foo.mFloat);
			Assert::AreEqual(foo["mString"].Get<std::string>(), foo.mString);
			Assert::IsTrue(foo["mVec4"].Get<glm::vec4>() == foo.mVec4);
			Assert::IsTrue(foo["mMat4"].Get<glm::mat4>() == foo.mMat4);
			Assert::IsTrue(&foo["mNestedScope"].Get<Scope>() == foo.mNestedScope);

			foo["mInt"] = mHelper.GetRandomInt32();
			foo["mFloat"] = mHelper.GetRandomFloat();
			foo["mString"] = mHelper.GetRandomString();
			foo["mVec4"] = mHelper.GetRandomVec4();
			foo["mMat4"] = mHelper.GetRandomMat4();

			Assert::AreEqual(foo["mInt"].Get<std::int32_t>(), foo.mInt);
			Assert::AreEqual(foo["mFloat"].Get<float>(), foo.mFloat);
			Assert::AreEqual(foo["mString"].Get<std::string>(), foo.mString);
			Assert::IsTrue(foo["mVec4"].Get<glm::vec4>() == foo.mVec4);
			Assert::IsTrue(foo["mMat4"].Get<glm::mat4>() == foo.mMat4);
			Assert::IsTrue(&foo["mNestedScope"].Get<Scope>() == foo.mNestedScope);

			bar["mInt"] = mHelper.GetRandomInt32();
			bar["mFloat"] = mHelper.GetRandomFloat();
			bar["mString"] = mHelper.GetRandomString();
			bar["mVec4"] = mHelper.GetRandomVec4();
			bar["mMat4"] = mHelper.GetRandomMat4();

			Assert::AreEqual(bar["mInt"].Get<std::int32_t>(), bar.mInt);
			Assert::AreEqual(bar["mFloat"].Get<float>(), bar.mFloat);
			Assert::AreEqual(bar["mString"].Get<std::string>(), bar.mString);
			Assert::IsTrue(bar["mVec4"].Get<glm::vec4>() == bar.mVec4);
			Assert::IsTrue(bar["mMat4"].Get<glm::mat4>() == bar.mMat4);
			Assert::IsTrue(&bar["mNestedScope"].Get<Scope>() == bar.mNestedScope);

			Assert::AreEqual(bar["mInt"].Get<std::int32_t>(), bar.mInt);
			Assert::AreEqual(bar["mFloat"].Get<float>(), bar.mFloat);
			Assert::AreEqual(bar["mString"].Get<std::string>(), bar.mString);
			Assert::IsTrue(bar["mVec4"].Get<glm::vec4>() == bar.mVec4);
			Assert::IsTrue(bar["mMat4"].Get<glm::mat4>() == bar.mMat4);
			Assert::IsTrue(&bar["mNestedScope"].Get<Scope>() == bar.mNestedScope);
		}

		TEST_METHOD(TestEquality)
		{
			Attributed att1, att2, att3;
			AttributedFoo foo1, foo2, foo3, foo4;
			AttributedBar bar1, bar2, bar3, bar4;

			foo1.mInt = mHelper.GetRandomInt32();
			foo1.mFloat = mHelper.GetRandomFloat();
			foo1.mString = mHelper.GetRandomString();
			foo1.mVec4 = mHelper.GetRandomVec4();
			foo1.mMat4 = mHelper.GetRandomMat4();

			bar1.mInt = mHelper.GetRandomInt32();
			bar1.mFloat = mHelper.GetRandomFloat();
			bar1.mString = mHelper.GetRandomString();
			bar1.mVec4 = mHelper.GetRandomVec4();
			bar1.mMat4 = mHelper.GetRandomMat4();

			att2 = att1;
			att3 = att1;
			att3.Append("test");
			Assert::IsTrue(att1 == att2);
			Assert::IsFalse(att1 != att2);
			Assert::IsFalse(att1 == att3);
			Assert::IsTrue(att1 != att3);

			foo2 = foo1;
			foo3 = foo1;
			foo3["mInt"] = mHelper.GetRandomInt32();
			Assert::IsTrue(foo1 == foo2);
			Assert::IsFalse(foo1 != foo2);
			Assert::IsFalse(foo1 == foo3);
			Assert::IsTrue(foo1 != foo3);
			Assert::IsFalse(foo1 == foo4);
			Assert::IsTrue(foo1 != foo4);

			bar2 = bar1;
			bar3 = bar1;
			bar3["mInt"] = mHelper.GetRandomInt32();
			Assert::IsTrue(bar1 == bar2);
			Assert::IsFalse(bar1 != bar2);
			Assert::IsFalse(bar1 == bar3);
			Assert::IsTrue(bar1 != bar3);
			Assert::IsFalse(bar1 == bar4);
			Assert::IsTrue(bar1 != bar4);
		}

		TEST_METHOD(TestCopyAuxiliaryAttributes)
		{
			Attributed attributed1;
			AttributedFoo foo1;
			AttributedBar bar1;

			std::uint32_t index = 0;
			for (auto& name : AuxiliaryAttributes)
			{
				initializers[index](attributed1.AddAuxiliaryAttribute(name));
				initializers[index](foo1.AddAuxiliaryAttribute(name + "Foo"));
				initializers[index](bar1.AddAuxiliaryAttribute(name + "Bar"));
				++index;
			}

			Attributed attributed2;
			AttributedFoo foo2;
			AttributedBar bar2;
			Assert::IsTrue(attributed2.AuxiliaryAttributes().IsEmpty());
			Assert::IsTrue(foo2.AuxiliaryAttributes().IsEmpty());
			Assert::IsTrue(bar2.AuxiliaryAttributes().IsEmpty());
			attributed2.CopyAuxiliaryAttributes(attributed1);
			foo2.CopyAuxiliaryAttributes(foo1);
			bar2.CopyAuxiliaryAttributes(bar1);
			Assert::IsTrue(attributed2.AuxiliaryAttributes() == attributed1.AuxiliaryAttributes());
			Assert::IsTrue(foo2.AuxiliaryAttributes() == foo1.AuxiliaryAttributes());
			Assert::IsTrue(bar2.AuxiliaryAttributes() == bar1.AuxiliaryAttributes());
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
		"mDatum",
		"mRtti",
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
		"mNestedScopeBar",
		"mIntBarInternal",
		"mFloatBarInternal",
		"mStringBarInternal",
		"mVec4BarInternal",
		"mMat4BarInternal"
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
