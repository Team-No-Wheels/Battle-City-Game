#include "Pch.h"
#include "UIElement.h"

namespace BattleCity
{
	ATTRIBUTED_DEFINITIONS(UIElement);

	UIElement::UIElement()
	{
		mSpriteName = "ColorBlack";
	}

	void UIElement::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	ENTITY_FACTORY_DEFINITIONS(UIElement);
}
