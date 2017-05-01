#include "Pch.h"
#include "UIElement.h"

namespace BattleCity
{
	ATTRIBUTED_DEFINITIONS(UIElement);


	void UIElement::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	ENTITY_FACTORY_DEFINITIONS(UIElement);
}
