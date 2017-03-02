#include "Pch.h"
#include "AttributedFoo.h"

namespace UnitTestLibraryDesktop
{
	ATTRIBUTED_DEFINITIONS(AttributedFoo, 2U)

	RTTI_DEFINITIONS(AttributedFoo)

	AttributedFoo::AttributedFoo() : mInt(0U), mFloat(0.0f)
	{
		AddExternalAttribute("mInt", mInt, 1U);
		AddExternalAttribute("mFloat", mFloat, 1U);
		ValidateAllPrescribedAttributesAreAdded();
	}

	AttributedFoo::~AttributedFoo()
	{
	}

	void AttributedFoo::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		prescribedAttributeNames.PushBack("mInt");
		prescribedAttributeNames.PushBack("mFloat");
	}
}
