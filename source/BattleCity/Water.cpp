#pragma once

#include "Pch.h"
#include "Water.h"

namespace BattleCity
{
	namespace MapEntities
	{
		ATTRIBUTED_DEFINITIONS(Water)
		ENTITY_FACTORY_DEFINITIONS(Water)

		Water::Water() :
			TileBase(TileType::WATER)
		{
		}

		void Water::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}
	}
}