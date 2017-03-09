#include "Pch.h"
#include "AttributedBar.h"

namespace UnitTestLibraryDesktop
{
	ATTRIBUTED_DEFINITIONS(AttributedBar)

	RTTI_DEFINITIONS(AttributedBar)

	AttributedBar::AttributedBar() :
		mIntBar(0), mFloatBar(0.0f), mNestedScopeBar(new Scope())
	{
		AddExternalAttribute("mIntBar", &mIntBar, 1);
		AddExternalAttribute("mFloatBar", &mFloatBar, 1);
		AddExternalAttribute("mStringBar", &mStringBar, 1);
		AddExternalAttribute("mVec4Bar", &mVec4Bar, 1);
		AddExternalAttribute("mMat4Bar", &mMat4Bar, 1);
		AddNestedScope("mNestedScopeBar", *mNestedScopeBar);
		ValidateAllPrescribedAttributesAreAdded();
	}

	AttributedBar::AttributedBar(const AttributedBar& rhs) :
		AttributedFoo(rhs), mIntBar(rhs.mIntBar), mFloatBar(rhs.mFloatBar), mNestedScopeBar(nullptr)
	{
		Copy(rhs);
	}

	AttributedBar::AttributedBar(AttributedBar&& rhs) noexcept :
		AttributedFoo(std::move(rhs)), mIntBar(rhs.mIntBar), mFloatBar(rhs.mFloatBar), mNestedScopeBar(nullptr)
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
		mIntBar = rhs.mIntBar;
		mFloatBar = rhs.mFloatBar;
		mStringBar = rhs.mStringBar;
		mVec4Bar = rhs.mVec4Bar;
		mMat4Bar = rhs.mMat4Bar;
		FixupPrescribedAttributes();
	}

	void AttributedBar::Move(AttributedBar& rhs)
	{
		mIntBar = rhs.mIntBar;
		mFloatBar = rhs.mFloatBar;
		mStringBar = std::move(rhs.mStringBar);
		mVec4Bar = std::move(rhs.mVec4Bar);
		mMat4Bar = std::move(rhs.mMat4Bar);
		FixupPrescribedAttributes();
	}

	void AttributedBar::FixupPrescribedAttributes()
	{
		(*this)["this"].Set(this);
		(*this)["mIntBar"].SetStorage(&mIntBar, 1);
		(*this)["mFloatBar"].SetStorage(&mFloatBar, 1);
		(*this)["mStringBar"].SetStorage(&mStringBar, 1);
		(*this)["mVec4Bar"].SetStorage(&mVec4Bar, 1);
		(*this)["mMat4Bar"].SetStorage(&mMat4Bar, 1);
		mNestedScopeBar = &(*this)["mNestedScopeBar"].Get<Scope>();
	}

	void AttributedBar::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		prescribedAttributeNames.PushBack("mIntBar");
		prescribedAttributeNames.PushBack("mFloatBar");
		prescribedAttributeNames.PushBack("mStringBar");
		prescribedAttributeNames.PushBack("mVec4Bar");
		prescribedAttributeNames.PushBack("mMat4Bar");
		prescribedAttributeNames.PushBack("mNestedScopeBar");
	}
}
