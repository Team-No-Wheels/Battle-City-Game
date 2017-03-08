#include "Pch.h"
#include "AttributedBar.h"

namespace UnitTestLibraryDesktop
{
	ATTRIBUTED_DEFINITIONS(AttributedBar, 6U)

	RTTI_DEFINITIONS(AttributedBar)

	AttributedBar::AttributedBar() :
		mInt(0), mFloat(0.0f), mNestedScope(new Scope())
	{
		AddExternalAttribute("mInt", &mInt, 1);
		AddExternalAttribute("mFloat", &mFloat, 1);
		AddExternalAttribute("mString", &mString, 1);
		AddExternalAttribute("mVec4", &mVec4, 1);
		AddExternalAttribute("mMat4", &mMat4, 1);
		AddNestedScope("mNestedScope", *mNestedScope);
		ValidateAllPrescribedAttributesAreAdded();
	}

	AttributedBar::AttributedBar(const AttributedBar& rhs) :
		AttributedFoo(rhs), mInt(rhs.mInt), mFloat(rhs.mFloat), mNestedScope(nullptr)
	{
		Copy(rhs);
	}

	AttributedBar::AttributedBar(AttributedBar&& rhs) noexcept :
		AttributedFoo(std::move(rhs)), mInt(rhs.mInt), mFloat(rhs.mFloat), mNestedScope(nullptr)
	{
		Move(rhs);
	}

	AttributedBar& AttributedBar::operator=(const AttributedBar& rhs)
	{
		if (this != &rhs)
		{
			AttributedFoo::operator=(rhs);
			Copy(rhs);
		}
		return *this;
	}

	AttributedBar& AttributedBar::operator=(AttributedBar&& rhs) noexcept
	{
		if (this != &rhs)
		{
			AttributedFoo::operator=(std::move(rhs));
			Move(rhs);
		}
		return *this;
	}

	void AttributedBar::Copy(const AttributedBar& rhs)
	{
		mInt = rhs.mInt;
		mFloat = rhs.mFloat;
		mString = rhs.mString;
		mVec4 = rhs.mVec4;
		mMat4 = rhs.mMat4;
		FixupPrescribedAttributes();
	}

	void AttributedBar::Move(AttributedBar& rhs)
	{
		mInt = rhs.mInt;
		mFloat = rhs.mFloat;
		mString = std::move(rhs.mString);
		mVec4 = std::move(rhs.mVec4);
		mMat4 = std::move(rhs.mMat4);
		FixupPrescribedAttributes();
	}

	void AttributedBar::FixupPrescribedAttributes()
	{
		(*this)["this"].Set(this);
		(*this)["mInt"].SetStorage(&mInt, 1);
		(*this)["mFloat"].SetStorage(&mFloat, 1);
		(*this)["mString"].SetStorage(&mString, 1);
		(*this)["mVec4"].SetStorage(&mVec4, 1);
		(*this)["mMat4"].SetStorage(&mMat4, 1);
		mNestedScope = &(*this)["mNestedScope"].Get<Scope>();
	}

	void AttributedBar::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		prescribedAttributeNames.PushBack("mInt");
		prescribedAttributeNames.PushBack("mFloat");
		prescribedAttributeNames.PushBack("mString");
		prescribedAttributeNames.PushBack("mVec4");
		prescribedAttributeNames.PushBack("mMat4");
		prescribedAttributeNames.PushBack("mNestedScope");
	}
}
