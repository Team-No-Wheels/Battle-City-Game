#include "Pch.h"
#include "AttributedFoo.h"

namespace UnitTestLibraryDesktop
{
	ATTRIBUTED_DEFINITIONS(AttributedFoo, 2U)

	RTTI_DEFINITIONS(AttributedFoo)

	AttributedFoo::AttributedFoo() : mInt(0U), mFloat(0.0f)
	{
		AddExternalAttribute("mInt", &mInt, 1U);
		AddExternalAttribute("mFloat", &mFloat, 1U);
		ValidateAllPrescribedAttributesAreAdded();
	}

	AttributedFoo::~AttributedFoo()
	{
	}

	AttributedFoo::AttributedFoo(const AttributedFoo& rhs) :
		Attributed(rhs), mInt(rhs.mInt), mFloat(rhs.mFloat)
	{
	}

	AttributedFoo::AttributedFoo(AttributedFoo&& rhs) noexcept :
		Attributed(std::move(rhs)), mInt(rhs.mInt), mFloat(rhs.mFloat)
	{
	}

	AttributedFoo& AttributedFoo::operator=(const AttributedFoo& rhs)
	{
		if (this != &rhs)
		{
			Attributed::operator=(rhs);
			mInt = rhs.mInt;
			mFloat = rhs.mFloat;
			operator[]("mInt").SetStorage(&mInt, 1);
			operator[]("mFloat").SetStorage(&mFloat, 1);
		}
		return *this;
	}

	AttributedFoo& AttributedFoo::operator=(AttributedFoo&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Attributed::operator=(std::move(rhs));
			mInt = rhs.mInt;
			mFloat = rhs.mFloat;
			operator[]("mInt").SetStorage(&mInt, 1);
			operator[]("mFloat").SetStorage(&mFloat, 1);
		}
		return *this;
	}

	void AttributedFoo::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		prescribedAttributeNames.PushBack("mInt");
		prescribedAttributeNames.PushBack("mFloat");
	}
}
