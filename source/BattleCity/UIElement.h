#pragma once

#include "Factory.h"
#include "GameObject.h"

namespace BattleCity
{
	class UIElement : public AnonymousEngine::Core::GameObject
	{
	public:
		UIElement();
		virtual ~UIElement() = default;

		ATTRIBUTED_DECLARATIONS(UIElement, AnonymousEngine::Core::GameObject);
	};

	ENTITY_FACTORY_DECLARATIONS(UIElement);
}
